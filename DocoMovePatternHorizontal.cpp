#pragma once
#include "DocoMovePatternHorizontal.h"
#include <vector>
#include "Directions.h"

Directions* moveHorDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::moveStrategy() {
	return moveHorDirs->getHorizontalPairOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::avoidanceStrategy() {
	// Implement horizontal movement avoidance strategy
	//          If an edge of the world is encountered the DOCO will randomly elect to move up
	//          or down a row and reverse its direction of movement.
	std::vector<std::pair<int, int> > avoidanceStrategy;
	avoidanceStrategy = moveHorDirs->getVerticalPairOffsets(); // Option to move up / down a row.
	return avoidanceStrategy;
}

DocoMovePatternHorizontal::DocoMovePatternHorizontal() : DocoMoveStrategy() {

}

DocoMovePatternHorizontal::~DocoMovePatternHorizontal() {

}

