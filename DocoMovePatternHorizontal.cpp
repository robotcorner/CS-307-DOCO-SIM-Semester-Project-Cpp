#pragma once
#include "DocoMovePatternHorizontal.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::moveStrategy() {
	return moveDirs->getVerticalPairOffsets();	// TODO: not sure which one is needed	
	// return moveDirs->getHorizontalPairOffsetsWithDir();	
}

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::avoidanceStrategy() {
	// TODO: implement horizontal movement avoidance strategy
	std::vector<std::pair<int, int> > avoidanceStrategy;
	avoidanceStrategy = moveDirs->getVerticalPairOffsets(); // Option to move up / down a row.
	// reverse direction of movement
	return avoidanceStrategy;
}

// TODO:	Behavior pattern 1 will cause the DOCO to move only in a horizontal direction. 
//          If an edge of the world is encountered the DOCO will randomly elect to move up
//          or down a row and reverse its direction of movement.