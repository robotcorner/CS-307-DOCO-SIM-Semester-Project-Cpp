#pragma once
#include "DocoMovePatternDiagonal.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternDiagonal::moveStrategy() {
	return moveDirs->getDiagonalPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getDiagonalPairOffsetsWithDir();	
}

// TODO:    Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.
//          If an edge of the world is encountered the DOCO will randomly elect to move 
//          left, right, up, or down and either reverse its direction of movement or move
//          in the other diagonal direction.