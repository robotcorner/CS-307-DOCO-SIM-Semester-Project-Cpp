#pragma once
#include "DocoMovePatternDefault.h"
#include "DocoMoveStrategy.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternDefault::moveStrategy() {
	return moveDirs->getXYOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternDefault::avoidanceStrategy() {
	// --- Implement normal move avoidance pair options to select if others don't work.
	return moveDirs->getXYOffsets(); // TODO: decide what offsets to get
}

DocoMovePatternDefault::DocoMovePatternDefault() {

}

DocoMovePatternDefault::~DocoMovePatternDefault() {

}