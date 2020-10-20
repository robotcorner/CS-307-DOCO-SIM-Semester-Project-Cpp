#pragma once
#include "Doco.h"
#include "Directions.h"
#include "CellGrid.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

Directions directions = Directions();

Doco::Doco(int x, int y, std::string &start_dir)
{
	this->position.first = x;
	this->position.second = y;
	this->setDirection(start_dir);
}

Doco::~Doco() {
	
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
	this->direction = directions.getPairComboForString(new_direction);
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

/*	REQUIREMENTS:
- [x] Each DOCO will always move in a straight line in its' current direction of movement unless that movement is modified by the constraints given below.
- [x] If a DOCO encounters an edge of the world that prevents it from proceeding on its current path it will select a random direction as its new heading. The new heading, however, must not take it into the cell of another DOCO.
- [x] If there is another DOCO in the next cell along a DOCO's current heading then the DOCO will select a random direction other than its current heading. The new heading, however, must not take it into the cell of another DOCO.
- [x] If a DOCO "smells" a food pellet in a cell bordering its' current location it will alter its heading to take it into that cell on the next move and that direction will become its new heading.
*/

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

std::pair<int, int> Doco::move(int world_w, int world_h) // returns the pair that moved too.
{
	// Setup move pair that is choosen
	int x = this->getXPos();
	int y = this->getYPos();
	std::pair<int, int> moving_here;		// new (x, y) position for DOCO.
	std::pair<int, int> temp_next_pos;
	std::pair<int, int> temp_next_valid_pos;
	std::pair<int, int> option;

	this->move_options.clear(); // Clear move options from previous turn to generate new ones now that new data is in.
	for (auto pair : this->adjoined_cells) {
		this->move_options.push_back(pair);
	}

	std::vector<std::pair<int, int> >::iterator it;
	std::vector<std::pair<int, int> >::iterator identifying_value;
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
				auto temp_next_dir = directions.getRandomDirectionPair();
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
				auto direction = directions.getDirForPair(std::make_pair(x, y), std::make_pair(identifying_value->first, identifying_value->second));
				// --- Set Current Direction to the pair.
				this->setDirection(direction);
			}
		}
		++it;
	}

	// --- Create move pair for continuing in same direciton or the direction of food
	temp_next_pos = std::make_pair(x + direction.second.first, y + direction.second.second); // actual x-y cord

	// Check temp_next_pos to see if valid.
	// Remove move options that involve out of bounds or collisions with other DOCOs.
	bool verified = false;
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
			auto temp_next_dir = directions.getRandomDirectionPair();
			this->setDirection(temp_next_dir.first);
			temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		}
	}
	moving_here = temp_next_valid_pos;
	
	// --- Update doco position and energy if it's still alive.
	if (this->getAlive())
	{
		if (x == moving_here.first && y == moving_here.second) { /* do nothing */ }
		else {
			this->energy_level -= 25; // 25 Energy per move. Only count if they moved to a new spot.
		}
		this->setPos(moving_here.first, moving_here.second);
		this->setAlive();
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

