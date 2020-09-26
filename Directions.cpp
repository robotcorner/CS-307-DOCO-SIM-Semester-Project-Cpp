#include "Directions.h"
#include <search.h>
#include <iostream>

std::vector<std::string> Directions::setMoveDirections(void) {
	static std::string move_directions[] = { "SW","W","NW","S","N","SE","E","NE" };
	return std::vector<std::string>(move_directions, (move_directions + (sizeof(move_directions) / sizeof(std::string))));
}

void Directions::setXYModifiers(void)
{
	std::pair<int, int> viable_pair;
	int i, j;
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			viable_pair = std::make_pair(i, j);
			xy_modifiers.push_back(viable_pair);
		}
	}
	xy_modifiers.shrink_to_fit();
}

void Directions::setDirXYPairs(void)
{
	for (int i = 0; i < 8; ++i)
	{
		this->dir_xy_pairs.push_back(std::make_pair(this->move_directions[i], this->xy_modifiers[i]));
	}
	this->dir_xy_pairs.shrink_to_fit();
}

Directions::Directions()
{
	this->move_directions = setMoveDirections();
	this->move_directions.shrink_to_fit();
	this->setXYModifiers();
	this->setDirXYPairs();
}

Directions::~Directions()
{
	
}

std::vector<std::string> Directions::getAllDirections(void)
{
	return this->move_directions;
}


void Directions::printDirXYPairs()
{
	for (auto i : this->dir_xy_pairs)
	{
		std::cout << i.first << "  (" << i.second.first << ", " << i.second.second << ")\n";
	}
}

std::vector<std::pair<std::string, std::pair<int, int>>> Directions::getDirectionPairs()
{
	return this->dir_xy_pairs;
}

std::pair<std::string, std::pair<int, int>> Directions::getPairComboForString(std::string dir)
{
	if (dir == "N") return this->dir_xy_pairs[4];
	else if (dir == "NE") return this->dir_xy_pairs[7];
	else if (dir == "E") return this->dir_xy_pairs[6];
	else if (dir == "SE") return this->dir_xy_pairs[5];
	else if (dir == "S") return this->dir_xy_pairs[3];
	else if (dir == "SW") return this->dir_xy_pairs[0];
	else if (dir == "W") return this->dir_xy_pairs[1];
	else if (dir == "NW") return this->dir_xy_pairs[2];
}