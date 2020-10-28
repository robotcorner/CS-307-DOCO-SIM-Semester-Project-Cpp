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

	/*
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
	*/

	/*
	- Each DOCO will always move in a straight line in its' current direction of movement unless that movement is modified by the constraints given below.

	*/

	// ----------------------------------------------------------------------------
	// | 1 | GO FOR FOOD IF AVAILABLE

	//  SMELL FOOD => it will alter its heading to food cell on next move. 
	//  The cell containing food does not have to be along its' path defined by its movement behavior.
	if (this->adjoined_food_cells.size() > 0) 
	{
		// Create move pair for jumping once in the direction of food and keeping heading
		temp_next_valid_pos = this->adjoined_food_cells.at(randObj->generateRandomNum(0, this->adjoined_food_cells.size() - 1)); // choose random food poition
		// TODO: alter heading for the food direction?
	}
	
	// ----------------------------------------------------------------------------
	// | 2 | CONTINUE IN SAME DIRECTION IF POSSIBLE
	
	// Check if path is open in Current Direction, if it is, pick it
	// If a DOCO "sees" an obstacle in the next cell along its current direction it 
	// will modify its movement to avoid that obstacle.
	else if (this->adjoined_open_cells.size() > 0) 
	{
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		identifying_value = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		if (identifying_value->first) // if there is an open position in that direction
		{
			// --- Choose open position
			temp_next_valid_pos = this->adjoined_open_cells.at(identifying_value->second);
		}
	}
	
	// ----------------------------------------------------------------------------
	// | 3 | WHEN OBSTACLE IS IN PATH, PICK RANDOM DIRECTION

	else if (this->adjoined_obstacle_cells.size() > 0) 
	{
		// --- Check if obstacle in current direction path, if it is, pick a random open direction
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		identifying_value = std::find(this->adjoined_obstacle_cells.begin(), adjoined_obstacle_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		if (identifying_value->first) // if there is an obstacle
		{
			// --- Choose random open position
			temp_next_valid_pos = this->adjoined_open_cells.at(randObj->generateRandomNum(0, this->adjoined_open_cells.size() - 1));
		}
		
	}
	
	// ----------------------------------------------------------------------------
	// | 4 | WHEN A WALL IS HIT, USE AVOIDANCE STRATEGY

	else if (this->adjoined_cells.size() < 8) 
	{
		// --- Check if wall in current direction path, if it is, pick a direction from movement stategy
		// Check for direction in adjoined_cells, if not in there then it hit a wall.
		
		// Make temporary next position continuing it's direction path.
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);

		// Make temporary next position continuing it's direction path.
		identifying_value = std::find(this->adjoined_cells.begin(), adjoined_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)

		// If there is not an position for this, it's a wall 
		if (!identifying_value->first)
		{
			// --- Move to a random avoidance strategy that is open
			auto avoidance_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
			auto temp_next_pos2 = avoidance_pair_vect.at(randObj->generateRandomNum(0, avoidance_pair_vect.size() - 1));	// does not check for obstacls or docos though :(
			auto identifying_value2 = std::find(this->adjoined_open_cells.begin(), this->adjoined_open_cells.end(), temp_next_pos2); // returns (bool, pos in searched vect)
			if (identifying_value2->first)
			{
				// --- Valid avoidence pair found.
				temp_next_valid_pos = temp_next_pos2;
				
				// --- Set reverse direction and allow the special case for diagonal.
				
				// Check if next position for direction is in the path
				auto temp_pair_vect = this->ptr_moveStrategy->moveStrategy();
				auto nonViablePos = std::find(temp_pair_vect.begin(), temp_pair_vect.end(), temp_next_pos); // returns (bool, pos in searched vect)

				// If next position is available for it's current path...
				if (nonViablePos->first)
				{
					auto pos = temp_pair_vect.begin() + identifying_value->second;
					temp_pair_vect.erase(pos);
					auto otherPairPos = temp_pair_vect.at(randObj->generateRandomNum(0, temp_pair_vect.size() - 1));
					// get direction from point
					std::string dir = directions->getDirForPair(this->direction.second, otherPairPos);
					this->setDirection(dir);
				}
			}
		}
	}

	// ----------------------------------------------------------------------------
	// | 5 | WHEN DIRECTION HITS ANOTHER DOCO, REVERSE, CHECK IF THAT'S A DOCO, IF IT IS, USE AVOIDANCE STRATEGY W/ RANDOM CHOICE
	
	else if (this->adjoined_occupied_cells.size() > 0) {
		this->ptr_moveStrategy->moveStrategy();
		
		// Make temporary next position continuing it's direction path.
		auto temp_next_dir = this->direction;
		temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		
		// Make temporary next position continuing it's direction path.
		identifying_value = std::find(this->adjoined_occupied_cells.begin(), adjoined_occupied_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		
		if (identifying_value->first) // if there is doco in that direction
		{
			// Reverse doco direction, but...for the move
			this->direction = directions->getOppositeDirectionPair(this->direction);
			// --- Check if doco in reverse direction
			auto temp_next_dir = this->direction;
			temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
			auto identifying_value2 = std::find(this->adjoined_occupied_cells.begin(), adjoined_occupied_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
			
			if (identifying_value2->first) // if there is doco in that direction
			{
				// --- doco in reverse direction, so choose random avoidance stragey
				auto temp_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
				temp_next_pos = temp_pair_vect.at(randObj->generateRandomNum(0, temp_pair_vect.size() - 1)); // choose random position from avoidance strategy.			
				auto validCheck = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)																												 // --- Choose open position
				if (validCheck->first) // if found in open cells
				{
					temp_next_valid_pos = this->adjoined_open_cells.at(identifying_value->second);
				}
			}
			else {
				// --- doco not in revese direction keep it
				// --- make sure it is in ajoined_open,don't want to turn into a wall or obstable
				auto validCheck = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)																												 // --- Choose open position
				if (validCheck->first) // if found in open cells
				{
					temp_next_valid_pos = this->adjoined_open_cells.at(identifying_value->second);
				}
			/*	else
				  temp_next_valid_pos = 0,0;  // Set to 0,0 so move same spot?
				  */
			}
		}
	}

	/*
	- Behavior Patterns

		o	Behavior pattern 1 will cause the DOCO to move only in a horizontal direction.If an edge of the
		world is encountered the DOCO will randomly elect to move up or down a row and reverse its direction
		of movement.

		o	Behavior pattern 2 will cause the DOCO to move only in a vertical direction.If an edge of the world
		is encountered the DOCO will randomly elect to move left or right a column and reverse its direction
		of movement.

		o	Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.If an edge of the world
		is encountered the DOCO will randomly elect to move left, right, up, or down and either reverse its
		direction of movement or move in the other diagonal direction.
	
	*/
	
	// --- Find nearby food in the valid move options that aren't occupied.
	/*
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
	*/

	// --- Create move pair for continuing in same direciton or the direction of food
	//temp_next_pos = std::make_pair(x + direction.second.first, y + direction.second.second); // actual x-y cord

	// Check temp_next_pos to see if valid. Remove move options that involve out of bounds or collisions with other DOCOs.
	
	/*
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
	*/

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