#include "Directions.h"
#include <search.h>
#include <iostream>
#include <random>

std::random_device seed; // initialize seed engine
std::mt19937 rng(seed()); // generate random num with Merseene_Twister engine
int generateRandomNum(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max);
	auto rand_int = uni(rng);
	return rand_int;
}

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

std::vector<std::pair<std::string, std::pair<int, int> > > Directions::getDirectionPairs()
{
	return this->dir_xy_pairs;
}

std::pair<std::string, std::pair<int, int> > Directions::getPairComboForString(std::string dir)
{
	if (dir == "N") return this->dir_xy_pairs.at(4);
	else if (dir == "NE") return this->dir_xy_pairs.at(7);
	else if (dir == "E") return this->dir_xy_pairs.at(6);
	else if (dir == "SE") return this->dir_xy_pairs.at(5);
	else if (dir == "S") return this->dir_xy_pairs.at(3);
	else if (dir == "SW") return this->dir_xy_pairs.at(0);
	else if (dir == "W") return this->dir_xy_pairs.at(1);
	else if (dir == "NW") return this->dir_xy_pairs.at(2);
	else return this->dir_xy_pairs.at(4);
}

std::string Directions::getDirForPair(std::pair<int, int> presentPair, std::pair<int, int> movePair)
{
	int d_y = movePair.second - presentPair.second;
	int d_x = movePair.first - presentPair.first;
	if (this->dir_xy_pairs.at(4).second.first == d_x && this->dir_xy_pairs.at(4).second.second == d_y) return "N";
	if (this->dir_xy_pairs.at(7).second.first == d_x && this->dir_xy_pairs.at(7).second.second == d_y) return "NE";
	if (this->dir_xy_pairs.at(6).second.first == d_x && this->dir_xy_pairs.at(6).second.second == d_y) return "E";
	if (this->dir_xy_pairs.at(5).second.first == d_x && this->dir_xy_pairs.at(5).second.second == d_y) return "SE";
	if (this->dir_xy_pairs.at(3).second.first == d_x && this->dir_xy_pairs.at(3).second.second == d_y) return "S";
	if (this->dir_xy_pairs.at(0).second.first == d_x && this->dir_xy_pairs.at(0).second.second == d_y) return "SW";
	if (this->dir_xy_pairs.at(1).second.first == d_x && this->dir_xy_pairs.at(1).second.second == d_y) return "W";
	if (this->dir_xy_pairs.at(2).second.first == d_x && this->dir_xy_pairs.at(2).second.second == d_y) return "NW";
	else return "N";
}


std::pair<std::string, std::pair<int, int> > Directions::getOppositeDirectionPair(std::pair<std::string, std::pair<int, int> > dir_xy_offset) {
	std::string direction = dir_xy_offset.first;
	std::pair<std::string, std::pair<int, int> > opposite;
	if (direction == "N") {
		opposite = this->getPairComboForString("S");
	}
	else if (direction == "NE") {
		opposite = this->getPairComboForString("SW");
	}
	else if (direction == "E") {
		opposite = this->getPairComboForString("W");
	}
	else if (direction == "SE") {
		opposite = this->getPairComboForString("NW");
	}
	else if (direction == "S") {
		opposite = this->getPairComboForString("N");
	}
	else if (direction == "SW") {
		opposite = this->getPairComboForString("NE");
	}
	else if (direction == "W") {
		opposite = this->getPairComboForString("E");
	}
	else if (direction == "NW") {
		opposite = this->getPairComboForString("SE");
	}
	return opposite;
}

std::pair<std::string, std::pair<int, int> > Directions::getRandomDirectionPair() {
	return this->dir_xy_pairs.at(generateRandomNum(0, 7));
}
