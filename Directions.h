#pragma once
#include <vector>
#include <string>

class Directions
{
private:
	std::vector<std::pair<int, int>> xy_modifiers;
	std::vector<std::pair<std::string, std::pair<int, int>>> dir_xy_pairs;
	std::vector<std::string> move_directions;
	std::vector<std::string> getMoveDirections();
	void setXYModifiers();
	void setDirXYPairs();
public:
	Directions();
	~Directions();
	std::vector<std::string> getAllDirections(void);
	void printDirXYPairs();
};

