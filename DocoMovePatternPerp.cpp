#pragma once
#include "DocoMovePatternPerp.h"
#include <vector>
#include "Directions.h"

Directions* movePerpDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternPerp::moveStrategy() {
	return movePerpDirs->getPerpPairOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternPerp::avoidanceStrategy() {
	return movePerpDirs->getDiagonalPairOffsets(); // TODO: decide what offsets to get
}

DocoMovePatternPerp::DocoMovePatternPerp() {

}

DocoMovePatternPerp::~DocoMovePatternPerp() {

}