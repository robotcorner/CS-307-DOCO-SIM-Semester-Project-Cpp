#pragma once
#include "DocoMovePatternVertical.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternVertical::moveStrategy() {
	return moveDirs->getVerticalPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getHorizontalPairOffsetsWithDir();	
}


//	TODO:   Behavior pattern 2 will cause the DOCO to move only in a vertical direction.
//          If an edge of the world is encountered the DOCO will randomly elect to move 
//          left or right a column and reverse its direction of movement.