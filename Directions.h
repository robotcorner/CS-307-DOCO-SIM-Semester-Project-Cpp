#pragma once
#include <vector>
#include <string>

class Directions
{
private:
	std::vector<std::pair<int, int> > xy_modifiers;
	std::vector<std::string> move_directions;

	std::vector<std::pair<std::string, std::pair<int, int> > > horizontal_offsets_with_dir;
	std::vector<std::pair<int, int> > horizontal_pair_offsets;
	std::vector<std::pair<std::string, std::pair<int, int> > > vertical_offsets_with_dir;
	std::vector<std::pair<int, int> > vertical_pair_offsets;
	std::vector<std::pair<std::string, std::pair<int, int> > > diagonal_offsets_with_dir;
	std::vector<std::pair<int, int> > diagonal_pair_offsets;
	std::vector<std::pair<std::string, std::pair<int, int> > > perp_offsets_with_dir;
	std::vector<std::pair<int, int> > perp_pair_offsets;

	std::vector<std::string> setMoveDirections();
	void setXYModifiers();
	void setDirXYPairs();
	void setPairPatterns();
public:
	std::vector<std::pair<std::string, std::pair<int, int> > > dir_xy_pairs;
	Directions();
	~Directions();
	
	std::vector<std::string> getAllDirections(void);
	std::vector<std::pair<std::string, std::pair<int, int> > > getDirectionPairs();
	std::vector<std::pair<int, int> > getXYOffsets();

	std::vector<std::pair<std::string, std::pair<int, int> > > getHorizontalPairOffsetsWithDir();
	std::vector<std::pair<int, int> > getHorizontalPairOffsets();
	std::vector<std::pair<std::string, std::pair<int, int> > > getVerticalPairOffsetsWithDir();
	std::vector<std::pair<int, int> > getVerticalPairOffsets();
	std::vector<std::pair<std::string, std::pair<int, int> > > getDiagonalPairOffsetsWithDir();
	std::vector<std::pair<int, int> > getDiagonalPairOffsets();
	std::vector<std::pair<std::string, std::pair<int, int> > > getPerpPairOffsetsWithDir();
	std::vector<std::pair<int, int> > getPerpPairOffsets();


	std::pair<std::string, std::pair<int, int> > getPairComboForString(std::string);
	std::pair<std::string, std::pair<int, int> > getOppositeDirectionPair(std::pair<std::string, std::pair<int, int> >);
	std::pair<std::string, std::pair<int, int> > getRandomDirectionPair();
	std::string getDirForPair(std::pair<int, int> presentPair, std::pair<int, int> movePair);
	void printDirXYPairs();

};

