#pragma once
#include "Doco.h"
#include "Directions.h"
#include "CellGrid.h"
#include <vector>
#include <algorithm>
#include <iterator>

Directions directions = Directions();

Doco::Doco(int x, int y, std::string &start_dir)
{
	this->position.first = x;
	this->position.second = y;
	this->setDirection(start_dir);
}

Doco::Doco(int x, int y) {
	this->position.first = x;
	this->position.second = y;
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
	// CellGrid.Matrix.SpecificCell.setFoodPresent(bool) and setSymbol(char),
	// TODO: make sure the following are updated: This call the CellGrid.Matrix.SpecificCell.setFoodPresent(bool) and setSymbol(char), removeAllFood() commands for the cell being eaten off of.
}

/*	REQUIREMENTS
TODO:
o	Each DOCO will always move in a straight line in its' current direction of movement unless that movement is modified by the constraints given below.
o	If a DOCO encounters an edge of the world that prevents it from proceeding on its current path it will select a random direction as its new heading. The new heading, however, must not take it into the cell of another DOCO.
o	If there is another DOCO in the next cell along a DOCO's current heading then the DOCO will select a random direction other than its current heading. The new heading, however, must not take it into the cell of another DOCO.
o	If a DOCO "smells" a food pellet in a cell bordering its' current location it will alter its heading to take it into that cell on the next move and that direction will become its new heading.
*/

// Does energy stay the same if move to orginal location as a final option?
// prioritize cells based off food amounts or some other status.
// make sure that a two docos say at (0, 1) and (0,3) don't both try to move into (0,2) on an iteration.
// maybe circumvent this by providing an order that the doco's moves are decided. make sure once one has decided,
// the board status for that cell gets updated to occupied. // could create a occupied_pending variable in Cell
//&

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
		identifying_value = std::find(this->adjoined_occupied_cells.begin(), adjoined_occupied_cells.end(), *it);
		if (identifying_value != this->adjoined_occupied_cells.end())
		{
			if (it->first == identifying_value->first && it->second == identifying_value->second)
			{
				it = this->move_options.erase(it);
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

	// TODO: Add Perfered option for nearby food. If food nearby go to that one instead.

	// --- Create move pair for continuing in same direciton
	temp_next_pos = std::make_pair(x + direction.second.first, y + direction.second.second); // actual x-y cord

	// Check temp_next_pos to see if valid.
	// Remove move options that involve out of bounds or collisions with other DOCOs.
	bool verified = false;
	while (!verified)
	{
		// find if that pair is in, and it's position in the adjoined_cells vector of pairs
		std::pair<bool, int> result = findItemInVect<std::pair<int, int> >(this->move_options, temp_next_pos);
		if (result.first && (this->move_options.at(result.second).first >= 0) && (this->move_options.at(result.second).second >= 0) &&
			(this->move_options.at(result.second).first < world_w) && (this->move_options.at(result.second).second < world_h)) 
		{
			// now we know that the next position for the same direction is valid.
			temp_next_valid_pos = temp_next_pos;
			verified = true;
		}
		else {
			// Chooses random spot based off available options 
			// if can't continue in current direction.
			// this->move_options.erase(this->adjoined_cells.begin() + result.second - 1); 
			auto temp_next_dir = directions.getRandomDirectionPair();
			temp_next_pos = std::make_pair(x + temp_next_dir.second.first, y + temp_next_dir.second.second);
		}
	}
	moving_here = temp_next_valid_pos;
	
	// update doco position and energy if it's still alive.
	if (this->getAlive()) // update doco info only if it's even alive.
	{
		if (x == moving_here.first && y == moving_here.second) { /* do nothing */ }
		else {
			this->energy_level -= 10; // 10 Energy per move. Only count if they moved to a new spot.
		}
		this->setPos(moving_here.first, moving_here.second);
		this->setAlive();
	}
	return moving_here;
}


void Doco::move(std::vector<std::pair<int, int> >) // choose your own move
{
	// check to make sure withing bounds first and nearbly cells.
	// moving = subtract 10 energy
	// check if energy = 0, kill DOCO if case
	// base next position based off of direction.first ("N") 
	// and direction.second (-1,0) which holds a cordinate pair accessible through
	// direction.second.first, and direction.second.second
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

