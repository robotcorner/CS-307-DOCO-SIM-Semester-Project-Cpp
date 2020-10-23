#pragma once
#include <vector>

class DocoMoveStrategy
{
	virtual std::vector<std::pair<int, int> > moveStrategy();
	virtual std::vector<std::pair<int, int> > avoidanceStrategy();
};

