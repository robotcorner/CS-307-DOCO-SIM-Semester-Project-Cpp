#pragma once
#include "DocoMovePatternDefault.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatterDefault::moveStrategy() {
	return moveDirs->getXYOffsets();	
}