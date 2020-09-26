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

void Doco::eat(int amount_eaten, std::string type="default") { // type is selected without needing to specify
	if (type == "default")
	{
		int food_e_value = 50;				// food energy value -> could make this a class if needed later.
		int total_replished_e = food_e_value * amount_eaten;
		this->addEnergy(total_replished_e);
	}
}

// Does energy stay the same if move to orginal location as a final option?
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