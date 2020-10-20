#pragma once
#include "DocoMovePatternPerp.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternPerp::moveStrategy() {
	return moveDirs->getPerpPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getHorizontalPairOffsetsWithDir();	
}
