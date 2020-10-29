#include "Directions.h"
#include <search.h>
#include <iostream>
#include "UniformRandom.h"

// TODO: Possibly declare directions as a singleton

UniformRandom* randObj = UniformRandom::getInstance();



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

void Directions::setPairPatterns(void) 
{
	this->horizontal_offsets_with_dir.push_back(std::make_pair("W", std::make_pair(-1, 0)));
	this->horizontal_offsets_with_dir.push_back(std::make_pair("E", std::make_pair(1, 0)));
	this->horizontal_pair_offsets.push_back(std::make_pair(-1, 0));
	this->horizontal_pair_offsets.push_back(std::make_pair(1, 0));
	this->horizontal_offsets_with_dir.shrink_to_fit();

	this->vertical_offsets_with_dir.push_back(std::make_pair("N", std::make_pair(0, -1)));
	this->vertical_offsets_with_dir.push_back(std::make_pair("S", std::make_pair(0, 1)));
	this->vertical_pair_offsets.push_back(std::make_pair(0, -1));
	this->vertical_pair_offsets.push_back(std::make_pair(0, 1));
	this->vertical_offsets_with_dir.shrink_to_fit();

	this->diagonal_offsets_with_dir.push_back(std::make_pair("NW", std::make_pair(-1, -1)));
	this->diagonal_offsets_with_dir.push_back(std::make_pair("NE", std::make_pair(1, -1)));
	this->diagonal_offsets_with_dir.push_back(std::make_pair("SW", std::make_pair(-1, 1)));
	this->diagonal_offsets_with_dir.push_back(std::make_pair("SE", std::make_pair(1, 1)));
	this->diagonal_pair_offsets.push_back(std::make_pair(-1, -1));
	this->diagonal_pair_offsets.push_back(std::make_pair(1, -1));
	this->diagonal_pair_offsets.push_back(std::make_pair(-1, 1));
	this->diagonal_pair_offsets.push_back(std::make_pair(1, 1));
	this->diagonal_offsets_with_dir.shrink_to_fit();

	this->perp_offsets_with_dir.push_back(std::make_pair("W", std::make_pair(-1, 0)));
	this->perp_offsets_with_dir.push_back(std::make_pair("E", std::make_pair(1, 0)));
	this->perp_offsets_with_dir.push_back(std::make_pair("N", std::make_pair(0, -1)));
	this->perp_offsets_with_dir.push_back(std::make_pair("S", std::make_pair(0, 1)));
	this->perp_pair_offsets.push_back(std::make_pair(-1, 0));
	this->perp_pair_offsets.push_back(std::make_pair(1, 0));
	this->perp_pair_offsets.push_back(std::make_pair(0, -1));
	this->perp_pair_offsets.push_back(std::make_pair(0, 1));
	this->perp_offsets_with_dir.shrink_to_fit();
}

Directions::Directions()
{
	this->move_directions = setMoveDirections();
	this->move_directions.shrink_to_fit();
	this->setXYModifiers();
	this->setDirXYPairs();
	this->setPairPatterns();
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

std::vector<std::pair<std::string, std::pair<int, int> > > Directions::getHorizontalPairOffsetsWithDir()
{
	return this->horizontal_offsets_with_dir;
}

std::vector<std::pair<int, int> > Directions::getHorizontalPairOffsets()
{
	return this->horizontal_pair_offsets;
}

std::vector<std::pair<std::string, std::pair<int, int> > > Directions::getVerticalPairOffsetsWithDir()
{
	return this->vertical_offsets_with_dir;
}

std::vector<std::pair<int, int> > Directions::getVerticalPairOffsets()
{
	return this->vertical_pair_offsets;
}

std::vector<std::pair<std::string, std::pair<int, int> > > Directions::getDiagonalPairOffsetsWithDir()
{
	return this->diagonal_offsets_with_dir;
}

std::vector<std::pair<int, int> > Directions::getDiagonalPairOffsets()
{
	return this->diagonal_pair_offsets;
}

std::vector<std::pair<std::string, std::pair<int, int> > > Directions::getPerpPairOffsetsWithDir()
{
	return this->perp_offsets_with_dir;
}

std::vector<std::pair<int, int> > Directions::getPerpPairOffsets()
{
	return this->perp_pair_offsets;
}

std::vector<std::pair<int, int> > Directions::getXYOffsets()
{
	return this->xy_modifiers;
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
	return this->dir_xy_pairs.at(randObj->generateRandomNum(0, 7));
}

std::pair<std::string, std::pair<int, int> > Directions::getRandomVerticalDirectionPair() {
	return this->vertical_offsets_with_dir.at(randObj->generateRandomNum(0, 1));
}

std::pair<std::string, std::pair<int, int> > Directions::getRandomHorizontalDirectionPair() {
	return this->horizontal_offsets_with_dir.at(randObj->generateRandomNum(0,1));
}

std::pair<std::string, std::pair<int, int> > Directions::getRandomDiagonalDirectionPair() {
	return this->diagonal_offsets_with_dir.at(randObj->generateRandomNum(0,3));
}

std::pair<std::string, std::pair<int, int> > Directions::getRandomPerpDirectionPair() {
	return this->perp_offsets_with_dir.at(randObj->generateRandomNum(0,3));
}

