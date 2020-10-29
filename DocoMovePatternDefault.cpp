#pragma once
#include "DocoMovePatternDefault.h"
#include "DocoMoveStrategy.h"
#include <vector>
#include "Directions.h"

Directions* moveDefaultDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternDefault::moveStrategy() {
	return moveDefaultDirs->getXYOffsets();
}

std::vector<std::pair<int, int> > DocoMovePatternDefault::avoidanceStrategy() {
	// --- Implement normal move avoidance pair options to select if others don't work.
	return moveDefaultDirs->getXYOffsets(); // TODO: decide what offsets to get
}

DocoMovePatternDefault::DocoMovePatternDefault() {

}

DocoMovePatternDefault::~DocoMovePatternDefault() {

}