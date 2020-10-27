#pragma once
#include "Doco.h"
#include "Directions.h"
#include "CellGrid.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include "DocoMoveStrategy.h"
#include "UniformRandom.h"

Directions* directions = new Directions();
UniformRandom* randObj = new UniformRandom();

Doco::Doco(int x, int y, std::string start_dir, std::string strategy)
{
	this->position.first = x;
	this->position.second = y;
	this->setDirection(start_dir);
	this->setStrategy(strategy);
}

// --- Just copy the Doco, don't half energy or anything
Doco::Doco(const Doco &origObj) {
	// current doco position = passed in doco position
	this->position.first = origObj.position.first;		// copy x
	this->position.second = origObj.position.second;	// copy y
	this->setDirection(origObj.direction.first);		// copy direction
	this->setStrategy(origObj.strategy);				// copy strategy string
	auto strat = origObj.ptr_moveStrategy;				// copy old move strat
	this->setPtrMoveStrategy(strat);					// set new doco to same move strat
}

Doco::~Doco() {
}

template <typename T>
std::pair<bool, int> findItemInVect(const std::vector<T>& vecItems, const T& item)
{
	std::pair<bool, int> result;
	auto it = std::find(vecItems.begin(), vecItems.end(), item);
	if (it != vecItems.end()) {
		// dynamic_cast<std::vector<std::pair<int, int> >::iterator>()
		result.second = distance(vecItems.begin(), it);
		//auto item = result.second;
		result.first = true;
	}
	else {
		result.first = false;
		result.second = -1;
	}
	return result;
}

void Doco::setPos(int x, int y)
{
	this->position.first = x;
	this->position.second = y;
}

void Doco::setPos(std::pair<int, int> cordinates)
{
	this->position = cordinates;
}

void Doco::setDirection(std::string new_direction)
{
	this->direction = directions->getPairComboForString(new_direction);
}

void Doco::setAlive(bool life) 
{
	this->alive = life;
}

void Doco::setAlive(void) 
{
	if (this->energy_level <= 0) this->alive = false;
	else this->alive = true;
}

void Doco::setEnergy(int new_e_level) 
{
	if (new_e_level >= 0) {
		this->energy_level = new_e_level;
	}
	else new_e_level = 0;
	this->alive = false;
}

void Doco::addEnergy(int added_energy) {
	this->energy_level += added_energy;
}

void Doco::eat(int amount_eaten, const std::string& type="default") { // type is selected without needing to specify
	if (type == "default")
	{
		int food_e_value = 50;				// food energy value -> could make this a class if needed later.
		int total_replished_e = food_e_value * amount_eaten;
		this->addEnergy(total_replished_e);
	}
}

std::pair<int, int> Doco::move(int world_w, int world_h) // returns the pair that moved too.
{
	// --- Setup move pair that is choosen
	int x = this->getXPos();
	int y = this->getYPos();
	std::pair<int, int> moving_here;		// new (x, y) position for DOCO.
	std::pair<int, int> temp_next_pos;
	std::pair<int, int> temp_next_valid_pos;
	std::pair<int, int> option;
	std::vector<std::pair<int, int> >::iterator it;
	std::vector<std::pair<int, int> >::iterator identifying_value;
	bool verified = false;

	this->move_options.clear(); // Clear move options from previous turn to generate new ones now that new data is in.
	for (auto pair : this->adjoined_cells) {
		this->move_options.push_back(pair);
	}

	// --- Remove move_options that contain occupied cells
	for (it = this->move_options.begin(); it != this->move_options.end(); )
	{
		// --- Find the location of where the move_option pair is that matches the adjoined_occupied_cell
		identifying_value = std::find(this->adjoined_occupied_cells.begin(), adjoined_occupied_cells.end(), *it);
		if (identifying_value != this->adjoined_occupied_cells.end())
		{
			if (it->first == identifying_value->first && it->second == identifying_value->second)
			{
				it = this->move_options.erase(it);
				// --- Create new random direction when nearby another doco in current heading
				auto temp_next_dir = directions->getRandomDirectionPair();
				this->setDirection(temp_next_dir.first);
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}


	if (this->adjoined_food_cells.size() > 0) {
		// If food is present, choose that spot, don't pick other locations.
		// --- Create move pair for continuing in same direciton or the direction of food
		temp_next_pos = this->adjoined_food_cells.at(randObj->generateRandomNum(0, this->adjoined_food_cells.size())); // choose random food poition
	}
	else if (this->adjoined_open_cells.size() > 0) {
		// --- Check if path is open in Current Direction, if it is, pick it
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		identifying_value = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		if (identifying_value->first) // if there is an open position in that direction
		{
			// --- Choose open position
			temp_next_pos = this->adjoined_open_cells.at(identifying_value->second);
		}
	}
	else if (this->adjoined_obstacle_cells.size() > 0) {
		// --- Check if obstacle in current direction path, if it is, pick a random open direction
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		identifying_value = std::find(this->adjoined_obstacle_cells.begin(), adjoined_obstacle_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		if (identifying_value->first) // if there is an obstacle
		{
			// --- Choose random open position
			temp_next_pos = this->adjoined_open_cells.at(randObj->generateRandomNum(0, this->adjoined_open_cells.size()));
		}
	}
	else if (this->adjoined_occupied_cells.size() < 8) {
		// ELSE CHECK CURRENT DIRECTION FOR WALL {Reverse Dir or Change Diag Dir(random change to remaining dir of stategy)} and move random open Avoidance strategy  //  HAVE WALL
		// --- Check if wall in current direction path, if it is, pick a direction from avoidance stategy
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		identifying_value = std::find(this->adjoined_cells.begin(), adjoined_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		if (!identifying_value->first) // if there is not an position for this, it's a wall 
		{
		// 1) Find Remaining Directions from Movement Strategy (random pick one) set direction
		//    remove current direction from movement strategy then random pick one NEED a TEMP MOVEMENT STRATEGY or do we

			auto move_strat_pair_vect = this->ptr_moveStrategy->moveStrategy();
			temp_next_pos = move_strat_pair_vect.at(randObj->generateRandomNum(0, move_strat_pair_vect.size()));	// does not check for obstacls or docos though :(
		
		// 2) Move to a random avoidance strategy that is open
			auto avoidance_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
			temp_next_pos = avoidance_pair_vect.at(randObj->generateRandomNum(0, avoidance_pair_vect.size()));	// does not check for obstacls or docos though :(
		
		}

	}
	else {
	// ELSE CHECK CURRENT DIRECTION FOR DOCO Reverse, if reverse point to DOCO then random open Avoidance strategy  //  HAVE DOCO
		this->ptr_moveStrategy->moveStrategy();
	}


	
	// --- Find nearby food in the valid move options that aren't occupied.
	for (it = this->move_options.begin(); it != this->move_options.end(); )
	{
		// --- Find the location of where the move_option pair is that matches a adjoined_food_cell
		identifying_value = std::find(this->adjoined_food_cells.begin(), adjoined_food_cells.end(), *it);
		if (identifying_value != this->adjoined_food_cells.end()) // If the value was found
		{
			// --- If the pairs match for the value found:
			if (it->first == identifying_value->first && it->second == identifying_value->second)
			{
				this->food_move_options.push_back(*identifying_value);
				// --- Choose last found pair to go to that contains food.
				// --- Extract Direction from this pair. 
				auto direction = directions->getDirForPair(std::make_pair(x, y), std::make_pair(identifying_value->first, identifying_value->second));
				// --- Set Current Direction to the pair.
				this->setDirection(direction);
			}
		}
		++it;
	}

	// --- Create move pair for continuing in same direciton or the direction of food
	temp_next_pos = std::make_pair(x + direction.second.first, y + direction.second.second); // actual x-y cord

	// Check temp_next_pos to see if valid. Remove move options that involve out of bounds or collisions with other DOCOs.

	while (!verified)
	{
		// --- Find if that pair is in, and it's position in the adjoined_cells vector of pairs
		std::pair<bool, int> result = findItemInVect<std::pair<int, int> >(this->move_options, temp_next_pos);
		if (result.first && (this->move_options.at(result.second).first >= 0) && (this->move_options.at(result.second).second >= 0) &&
			(this->move_options.at(result.second).first < world_w) && (this->move_options.at(result.second).second < world_h)) 
		{
			// --- The next position for the same direction is valid.
			temp_next_valid_pos = temp_next_pos;
			verified = true;
		}
		else {
			// --- Chooses random spot based off available options if it can't continue in current direction.
			auto temp_next_dir = directions->getRandomDirectionPair();
			this->setDirection(temp_next_dir.first);
			temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		}
	}
	moving_here = temp_next_valid_pos;
	
	// --- Update doco position and energy if it's still alive.
	if (this->getAlive()) // if alive, update position
	{
		docoMoveToPos(moving_here);
	}
	return moving_here;
}

bool Doco::getAlive()
{
	return this->alive;
}

std::pair<int, int> Doco::getPosPair(void)
{
	return this->position;
}

int Doco::getXPos() // returns whether the DOCO is alive or dead.
{
	return this->position.first;
}

int Doco::getYPos() // returns the current position of the DOCO
{
	return this->position.second;
}

std::pair<std::string, std::pair<int, int> > Doco::getDirection() // returns the current direction of the DOCO
{
	return this->direction;
}

std::string Doco::getDirectionString() 
{
	return this->direction.first;
}

int Doco::getEnergy() // returns the energy_level of the DOCO
{
	return this->energy_level;
}

void Doco::setStrategy(std::string strat)
{
	this->strategy = strat;
}

void Doco::setPtrMoveStrategy(DocoMoveStrategy* strat) {
	// TODO: figure out how to set the correct stategy (VERY IMPORTANT)
	this->ptr_moveStrategy = strat;
}

std::pair<int, int> Doco::docoMoveToPos(std::pair<int, int> moving_here ) {
	if (this->getXPos() == moving_here.first && this->getYPos() == moving_here.second) { /* do nothing */ }
	else {
		this->energy_level -= 25; // 25 Energy per move. Only count if they moved to a new spot.
	}
	this->setPos(moving_here.first, moving_here.second);
	this->setAlive();
}

DocoMoveStrategy* Doco::getPtrMoveStrategy() {
	return this->ptr_moveStrategy;
}