#pragma once
#include "DocoMovePatternPerp.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternPerp::moveStrategy() {
	return moveDirs->getPerpPairOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternPerp::avoidanceStrategy() {
	return moveDirs->getDiagonalPairOffsets(); // TODO: decide what offsets to get
}

DocoMovePatternPerp::DocoMovePatternPerp() {

}

DocoMovePatternPerp::~DocoMovePatternPerp() {

}