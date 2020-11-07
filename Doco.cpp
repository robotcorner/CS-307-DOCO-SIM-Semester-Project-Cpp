#pragma once
#include "Doco.h"
#include "Directions.h"
#include "CellGrid.h"
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include "UniformRandom.h"

Directions* directions = new Directions();
UniformRandom* randDocoObj = UniformRandom::getInstance();

Doco::Doco(int x, int y, std::string start_dir, std::string strategy) : AbstractDoco()
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
	else {
		new_e_level = 0;
		this->alive = false;
	}
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
	std::pair<bool, int> searchResult;

	
	bool found_next_valid_pos = false;
	temp_next_valid_pos = this->position;  // move to same spot if nothing else found
	
	auto temp_next_dir = this->direction;
	temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
	        ///////////////////////////////////////////////
			// TRY CURRENT DIRECTION UNLESS FOOD IS AROUND
			///////////////////////////////////////////////
	if (!found_next_valid_pos) {     // | 0 | CONTINUE IN SAME DIRECTION IF POSSIBLE	
		//identifying_value = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
		// the above fails, need to prevent the following to execute...heap error
		if(temp_next_pos.first > world_w || temp_next_pos.first < 0 || temp_next_pos.second > world_h || temp_next_pos.second < 0)
			searchResult.first=false; //outside range, don't bother checking
		else
		   searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos);
		if (searchResult.first) // Found an open position in current direction, otherwise try something else
		{
			if (this->adjoined_open_cells_with_food.size() == 0)  // No surrounding food
			{
				temp_next_valid_pos = this->adjoined_open_cells.at(searchResult.second);		// --- Choose current open position no food
				found_next_valid_pos = true;
			}
			else  // Check for food in current direction, 1st choice
			{
				std::pair<bool, int> searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells_with_food, temp_next_pos);
				if (searchResult.first)  //Food in current Direction, YumYum, otherwise find food in other directions below
				{
					temp_next_valid_pos = this->adjoined_open_cells_with_food.at(searchResult.second); // choose current open poition food
					found_next_valid_pos = true;
				}
			}
		}
	}
	                                 ///////////////////////////////////////////////
	                                 // | 1 | LOOK FOR FOOD IN AJOINING CELLS
									 ///////////////////////////////////////////////
	if (!found_next_valid_pos) {    
		if (this->adjoined_open_cells_with_food.size() > 0) // Food is avail, Pick one
		{
			// Create move pair for jumping once in the direction of food and keeping current heading
			temp_next_valid_pos = this->adjoined_open_cells_with_food.at(randDocoObj->generateRandomNum(0, int(this->adjoined_open_cells_with_food.size()) - 1)); // choose random food poition
			found_next_valid_pos = true;
		}
	}
	                                   ///////////////////////////////////////////////
                                       // | 2 | CHECK IF HIT WALL, USE AVOIDANCE STRATEGY
                                       ///////////////////////////////////////////////
	if (!found_next_valid_pos) { 
		if (this->adjoined_cells.size() < 8)  // Walls somewhere around doco
		{
			// --- Check if wall in current direction path, if it is, pick a direction from movement stategy
			// Check for direction in adjoined_cells, if not in there then it hit a wall..
			//searchResult = std::find(this->adjoined_cells.begin(), adjoined_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
			searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_cells, temp_next_pos); // searchResult = wall pair
			if (!searchResult.first) // If there is not an position for this, it's a wall 
			{
				// --- Change Direction to a random movement strategy minus current direction
				auto temp_next_dir = this->direction;
				// Create movement vectors
				std::pair<bool, int> movement_pair;
				auto movement_pair_vect = this->ptr_moveStrategy->moveStrategy();
				std::pair<int, int> temp_movement_pos;
				//for (auto i = movement_pair_vect.end(); i > movement_pair_vect.begin(); --i)
				for (auto i = int(movement_pair_vect.size()); i > 0; --i)
				{ // Remove cur direction vector
					temp_movement_pos = std::make_pair(movement_pair_vect.at(i - 1).first, movement_pair_vect.at(i - 1).second);
					if (temp_movement_pos.first == this->direction.second.first && temp_movement_pos.second == this->direction.second.second)
					{
						movement_pair_vect.erase(movement_pair_vect.begin() + i - 1);
					}
				}
				if (movement_pair_vect.size() > 0) {  // Randomly Pick a Movement Strategy for a direction - Reverse or Other line for diag and perp
					temp_movement_pos = movement_pair_vect.at(randDocoObj->generateRandomNum(0, int(movement_pair_vect.size()) - 1)); // choose random position from movement strategy.
					temp_next_dir.first = directions->getDirForOffset(temp_movement_pos);
					temp_next_dir.second.first = temp_movement_pos.first;
					temp_next_dir.second.second = temp_movement_pos.second;
					this->direction =temp_next_dir; // Change Direction
				}

				// --- Move to a random avoidance strategy that is open
				// Create open avoidance vectors
				std::pair<bool, int> avoidance_pair;
				auto avoidance_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
				//for (auto i = avoidance_pair_vect.end(); i > avoidance_pair_vect.begin(); --i)
				for (auto i = int(avoidance_pair_vect.size()); i > 0; --i)
				{ // Remove all vectors not open
					std::pair<int, int> temp_avoidance_pos = std::make_pair(x + avoidance_pair_vect.at(i-1).first, y + avoidance_pair_vect.at(i-1).second);
					if (temp_avoidance_pos.first >= world_w || temp_avoidance_pos.first < 0 || temp_avoidance_pos.second >= world_h || temp_avoidance_pos.second < 0)
					{
						avoidance_pair.first = false; 
						avoidance_pair.second = i - 1; //outside range, don't bother checking for open
					}
					else
					   avoidance_pair = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_avoidance_pos); // returns (bool, pos in searched vect)
					if (!avoidance_pair.first) // avoidance not open or outside range, remove vector
					{
						avoidance_pair_vect.erase(avoidance_pair_vect.begin()+i-1);
					}
				}
				if (avoidance_pair_vect.size() > 0) {  // Randomly Pick a Avoidance Strategy
					std::pair<int, int> temp_avoidance_pos = avoidance_pair_vect.at(randDocoObj->generateRandomNum(0, int(avoidance_pair_vect.size()) - 1)); // choose random position from avoidance strategy.
					temp_next_valid_pos = std::make_pair(x + temp_avoidance_pos.first, y + temp_avoidance_pos.second);
					found_next_valid_pos = true;
				}
			}
		}
	}
	                              ///////////////////////////////////////////////
                                  // | 3 | WHEN OBSTACLE IS IN PATH, PICK RANDOM DIRECTION in an OPEN PATH.
                                  ///////////////////////////////////////////////
	if (!found_next_valid_pos) {  
		if (this->adjoined_obstacle_cells.size() > 0) // Obstacles somewhere around doco
		{
			// --- Check if obstacle in current direction path, if it is, pick a random open direction
			searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_obstacle_cells, temp_next_pos); // returns (bool, pos in searched vect)
			if (searchResult.first) // if there is an obstacle
			{
				// --- Choose random open position
				temp_next_valid_pos = this->adjoined_open_cells.at(randDocoObj->generateRandomNum(0, int(this->adjoined_open_cells.size()) - 1));
				found_next_valid_pos = true;
			}
		}
	}
	                      ///////////////////////////////////////////////
                          // | 4 | WHEN DIRECTION HITS ANOTHER DOCO, REVERSE, CHECK IF THAT'S A DOCO, IF IT IS, USE AVOIDANCE STRATEGY W/ RANDOM CHOICE.
                          ///////////////////////////////////////////////
	if (!found_next_valid_pos) { 
		if (this->adjoined_occupied_cells.size() > 0) {
			//this->ptr_moveStrategy->moveStrategy();

			std::pair<bool, int> other_doco_pair = findItemInVect<std::pair<int, int> >(this->adjoined_occupied_cells, temp_next_pos); // returns (bool, pos in searched vect)
			if (other_doco_pair.first) // if there is doco in Current direction
			{
				auto temp_next_dir = this->direction;
				this->direction = directions->getOppositeDirectionPair(temp_next_dir); // Reverse doco direction, but...for the move
				
				// --- Check if doco in reverse direction
				temp_next_dir = this->direction;
				std::pair<bool, int> other_doco_pair2;
				temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
				if (temp_next_pos.first >= world_w || temp_next_pos.first < 0 || temp_next_pos.second >= world_h || temp_next_pos.second < 0)
					other_doco_pair2.first = false; //outside range, don't bother checking
				else
				   other_doco_pair2 = findItemInVect<std::pair<int, int> >(this->adjoined_occupied_cells, temp_next_pos); // returns (bool, pos in searched vect)
				if (other_doco_pair2.first) // if there is doco in the reverse direction
				{
					// --- doco in reverse direction, so choose random avoidance stragey
				    // Create open avoidance vectors
					auto avoidance_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
					std::pair<bool, int> avoidance_pair;
					//for (auto i = avoidance_pair_vect.end(); i > avoidance_pair_vect.begin(); --i)
					for (auto i = int(avoidance_pair_vect.size()); i > 0; --i)
					{ // Remove all vectors not open
						std::pair<int, int> temp_avoidance_pos = std::make_pair(x + avoidance_pair_vect.at(i-1).first, y + avoidance_pair_vect.at(i-1).second);
						if (temp_avoidance_pos.first >= world_w || temp_avoidance_pos.first < 0 || temp_avoidance_pos.second >= world_h || temp_avoidance_pos.second < 0) // 0 too (h-1)
						{
							avoidance_pair.first = false;
							avoidance_pair.second = i - 1; //outside range, don't bother checking for open
						}
						else
						   avoidance_pair = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_avoidance_pos); // returns (bool, pos in searched vect)
						if (!avoidance_pair.first) // avoidance not open or outside range, remove vector
						{
							avoidance_pair_vect.erase(avoidance_pair_vect.begin() +i-1);
						}
					}
					if (avoidance_pair_vect.size() > 0) {  // Randomly Pick a Avoidance Strategy
						std::pair<int, int> temp_avoidance_pos = avoidance_pair_vect.at(randDocoObj->generateRandomNum(0, int(avoidance_pair_vect.size()) - 1)); // choose random position from avoidance strategy.
						temp_next_valid_pos = std::make_pair(x + temp_avoidance_pos.first, y + temp_avoidance_pos.second);
						found_next_valid_pos = true;
					}
				}
				else {
					// --- doco not in revese direction keep it
					// --- make sure it is in ajoined_open,don't want to turn into a wall or obstable
					std::pair<bool, int> validCheck = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos); // returns (bool, pos in searched vect)																											 // --- Choose open position
					if (validCheck.first) // if found in open cells
					{
						temp_next_valid_pos = temp_next_pos;
						found_next_valid_pos = true;
					}
					else {
						temp_next_valid_pos = this->position;  // move to same spot?
						found_next_valid_pos = true;
					}
				}
			}

		}
	}

	
   ///////////////////////////////////////////////
   //  THE ACTUAL MOVE
   ///////////////////////////////////////////////
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

// std::pair<int, int> Doco::docoMoveToPos(std::pair<int, int> moving_here ) {
	void Doco::docoMoveToPos(std::pair<int, int> moving_here) {

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