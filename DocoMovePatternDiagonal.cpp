#pragma once
#include "DocoMovePatternDiagonal.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternDiagonal::moveStrategy() {
	return moveDirs->getDiagonalPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getDiagonalPairOffsetsWithDir();	
}
