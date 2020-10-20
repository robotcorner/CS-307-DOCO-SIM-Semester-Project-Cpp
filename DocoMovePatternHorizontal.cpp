#pragma once
#include "DocoMovePatternHorizontal.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::moveStrategy() {
	return moveDirs->getVerticalPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getHorizontalPairOffsetsWithDir();	
}
