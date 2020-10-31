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

	/*
	- Each DOCO will always move in a straight line in its' current direction of movement unless that movement is modified by the constraints given below.
	*/

	// ----------------------------------------------------------------------------
	// | 1 | CONTINUE IN SAME DIRECTION IF POSSIBLE	
	auto temp_next_dir = this->direction;
	temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
	identifying_value = std::find(this->adjoined_open_cells.begin(), adjoined_open_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
	std::pair<bool, int> searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos);
	bool verified_bounds = false;
	while (!verified_bounds) {
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
		
		if (searchResult.first) // if there is an open position in that direction
		{
			temp_next_valid_pos = this->adjoined_open_cells.at(searchResult.second);		// --- Choose open position
			// | 5 | GO FOR FOOD IF AVAILABLE
			//  The cell containing food does not have to be along its' path defined by its movement behavior.
			if (this->adjoined_open_cells_with_food.size() > 0)
			{
				// Create move pair for jumping once in the direction of food and keeping heading
				temp_next_valid_pos = this->adjoined_open_cells_with_food.at(randDocoObj->generateRandomNum(0, int(this->adjoined_open_cells_with_food.size()) - 1)); // choose random food poition
			}
		}
		else // if can't continue in straight direction or jump to food, check if it's an obstacle in the way, check if it's a wall
		{
			// | 2 | WHEN A WALL IS HIT, USE AVOIDANCE STRATEGY
			if (this->adjoined_cells.size() < 8)
			{
				// --- Check if wall in current direction path, if it is, pick a direction from movement stategy
				// Check for direction in adjoined_cells, if not in there then it hit a wall..
				//searchResult = std::find(this->adjoined_cells.begin(), adjoined_cells.end(), temp_next_pos); // returns (bool, pos in searched vect)
				searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_cells, temp_next_pos); // searchResult = wall pair
				if (!searchResult.first) // If there is not an position for this, it's a wall 
				{
					// --- Move to a random avoidance strategy that is open
					auto avoidance_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();

					auto rand_avoid_pair = avoidance_pair_vect.at(randDocoObj->generateRandomNum(0, int(avoidance_pair_vect.size()) - 1));
					temp_next_pos = std::make_pair(x + rand_avoid_pair.first, y + rand_avoid_pair.second);
					auto avoid_pair_available = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos); // returns (bool, pos in searched vect)
					int attempts = 12;
					while (!avoid_pair_available.first && attempts < 15) {
						auto rand_avoid_pair = avoidance_pair_vect.at(randDocoObj->generateRandomNum(0, int(avoidance_pair_vect.size()) - 1));
						temp_next_pos = std::make_pair(x + rand_avoid_pair.first, y + rand_avoid_pair.second);
						auto avoid_pair_available = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos); // returns (bool, pos in searched vect)
						attempts++;
					}

					if (avoid_pair_available.first) // if avoid pair found in open cells
					{
						temp_next_valid_pos = temp_next_pos; // valid avoidence pair found.

						// --- Set reverse direction and allow the special case for diagonal.
						auto temp_pair_vect = this->ptr_moveStrategy->moveStrategy(); // Check if next position for direction is in the path
						auto viablePos = findItemInVect<std::pair<int, int> >(temp_pair_vect, temp_next_pos); // returns (bool, pos in searched vect)

						if (viablePos.first) // If next position is available for it's current path...
						{
							auto pos = temp_pair_vect.begin() + identifying_value->second;
							temp_pair_vect.erase(pos);
							auto otherPairPos = temp_pair_vect.at(randDocoObj->generateRandomNum(0, int(temp_pair_vect.size()) - 1));
							// get direction from point
							std::string dir = directions->getDirForPair(this->direction.second, otherPairPos);
							this->setDirection(dir);
						}
					}
				}
			}
			// | 3 | WHEN OBSTACLE IS IN PATH, PICK RANDOM DIRECTION in an OPEN PATH.
			else if (this->adjoined_obstacle_cells.size() > 0)
			{
				// --- Check if obstacle in current direction path, if it is, pick a random open direction
				auto temp_next_dir = this->direction;
				temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
				std::pair<bool, int> searchResult = findItemInVect<std::pair<int, int> >(this->adjoined_obstacle_cells, temp_next_pos); // returns (bool, pos in searched vect)
				if (searchResult.first) // if there is an obstacle
				{
					// --- Choose random open position
					temp_next_valid_pos = this->adjoined_open_cells.at(randDocoObj->generateRandomNum(0, int(this->adjoined_open_cells.size()) - 1));
				}
			}
			// | 4 | WHEN DIRECTION HITS ANOTHER DOCO, REVERSE, CHECK IF THAT'S A DOCO, IF IT IS, USE AVOIDANCE STRATEGY W/ RANDOM CHOICE
			else if (this->adjoined_occupied_cells.size() > 0) {
				this->ptr_moveStrategy->moveStrategy();

				std::pair<bool, int> other_doco_pair = findItemInVect<std::pair<int, int> >(this->adjoined_occupied_cells, temp_next_pos); // returns (bool, pos in searched vect)
				if (other_doco_pair.first) // if there is doco in that direction
				{
					this->direction = directions->getOppositeDirectionPair(this->direction); // Reverse doco direction, but...for the move

					// --- Check if doco in reverse direction
					auto temp_next_dir = this->direction;
					temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
					std::pair<bool, int> other_doco_pair2 = findItemInVect<std::pair<int, int> >(this->adjoined_occupied_cells, temp_next_pos); // returns (bool, pos in searched vect)
					if (other_doco_pair2.first) // if there is doco in that direction
					{
						// --- doco in reverse direction, so choose random avoidance stragey
						auto temp_pair_vect = this->ptr_moveStrategy->avoidanceStrategy();
						temp_next_pos = temp_pair_vect.at(randDocoObj->generateRandomNum(0, int(temp_pair_vect.size()) - 1)); // choose random position from avoidance strategy.			
						std::pair<bool, int> validCheck = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos); // returns (bool, pos in searched vect)																												 // --- Choose open position
						if (validCheck.first) // if found in open cells
						{
							temp_next_valid_pos = this->adjoined_open_cells.at(identifying_value->second);
						}
					}
					else {
						// --- doco not in revese direction keep it
						// --- make sure it is in ajoined_open,don't want to turn into a wall or obstable
						std::pair<bool, int> validCheck = findItemInVect<std::pair<int, int> >(this->adjoined_open_cells, temp_next_pos); // returns (bool, pos in searched vect)																											 // --- Choose open position
						if (validCheck.first) // if found in open cells
						{
							temp_next_valid_pos = this->adjoined_open_cells.at(identifying_value->second);
						}
						else temp_next_valid_pos = this->position;  // move to same spot?
					}
				}
			}
		}	
		
		// continue looping until item within the bounds of the map
		// --- Find if that pair is in, and it's position in the adjoined_cells vector of pairs
		std::pair<bool, int> result = findItemInVect<std::pair<int, int> >(this->adjoined_cells, temp_next_valid_pos);
		if (result.first && (this->adjoined_cells.at(result.second).first >= 0) && (this->adjoined_cells.at(result.second).second >= 0) &&
			(this->adjoined_cells.at(result.second).first < world_w) && (this->adjoined_cells.at(result.second).second < world_h))
		{
			// --- The next position for the same direction is valid.
			temp_next_valid_pos = temp_next_pos;
			verified_bounds = true;
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