#include "Doco.h"

Doco::Doco(int x, int y, std::string start_dir)
{
	this->position.first = x;
	this->position.second = y;
	this->direction = start_dir;
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
	//std::array<
	this->direction = new_direction;
}
