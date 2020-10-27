#pragma once
#include "DocoMovePatternVertical.h"
#include <vector>
#include "Directions.h"

// Behavior pattern 2 will cause the DOCO to move only in a vertical direction.

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternVertical::moveStrategy() {
	return moveDirs->getVerticalPairOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternVertical::avoidanceStrategy() {
	// --- Implement the avoidance strategy for vertical pattern avoidance
	//     If an edge of the world is encountered the DOCO will randomly elect to move 
	//     left or right a column and reverse its direction of movement.
	return moveDirs->getHorizontalPairOffsets(); 

}

DocoMovePatternVertical::DocoMovePatternVertical() {

}

DocoMovePatternVertical::~DocoMovePatternVertical() {

}

