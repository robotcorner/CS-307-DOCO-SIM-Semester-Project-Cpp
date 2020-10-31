#pragma once
#include <vector>

class DocoMoveStrategy		// Interface for DocoStrategy
{
public:
	virtual std::vector<std::pair<int, int> > moveStrategy() = 0;
	virtual std::vector<std::pair<int, int> > avoidanceStrategy() = 0;
};

