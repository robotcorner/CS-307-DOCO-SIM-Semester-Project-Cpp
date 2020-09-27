#include "Doco.h"
#include "Directions.h"
#include "CellGrid.h"

Directions directions = Directions();

Doco::Doco(int x, int y, std::string start_dir)
{
	this->position.first = x;
	this->position.second = y;
	this->direction = directions.getPairComboForString(start_dir);
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

// Does energy stay the same if move to orginal location as a final option?
// Default move to rand direction, but make sure in the future it is able to
// prioritize cells based off food amounts or some other status.
// make sure that a two docos say at (0, 1) and (0,3) don't both try to move into (0,2) on an iteration.
// maybe circumvent this by providing an order that the doco's moves are decided. make sure once one has decided,
// the board status for that cell gets updated to occupied. // could create a occupied_pending variable in Cell
// object to prevent grid locks of some kind...
void Doco::move(void)
{
	// TODO: do movement based off of the private variables available. Choose best option
	// do NOT collide with other DOCOs. Choose new directions when going to hit past edge
	// or collide.
	// chooses random spot based off available options.... maybe prioritze one with more food.
	// moving = subtract 10 energy
	// check if energy = 0, kill DOCO if case
	// base next position based off of direction.first ("N") 
	// and direction.second (-1,0) which holds a cordinate pair accessible through
	// direction.second.first, and direction.second.second
}

void Doco::move(int, int) // choose your own move
{
	// check to make sure withing bounds first
	// moving = subtract 10 energy
	// check if energy = 0, kill DOCO if case
	// base next position based off of direction.first ("N") 
	// and direction.second (-1,0) which holds a cordinate pair accessible through
	// direction.second.first, and direction.second.second
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

/*	REQUIREMENTS
o	Before the simulation starts each DOCO will randomly select a starting direction in which to move. This may be to the North, Northeast, East, Southeast, South, Southwest, West, or Northwest.
o	Each DOCO will always move in a straight line in its' current direction of movement unless that movement is modified by the constraints given below.
o	If a DOCO encounters an edge of the world that prevents it from proceeding on its current path it will select a random direction as its new heading. The new heading, however, must not take it into the cell of another DOCO.
o	If there is another DOCO in the next cell along a DOCO's current heading then the DOCO will select a random direction other than its current heading. The new heading, however, must not take it into the cell of another DOCO.
o	If a DOCO "smells" a food pellet in a cell bordering its' current location it will alter its heading to take it into that cell on the next move and that direction will become its new heading.
*/

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

std::pair<std::string, std::pair<int, int>> Doco::getDirection() // returns the current direction of the DOCO
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