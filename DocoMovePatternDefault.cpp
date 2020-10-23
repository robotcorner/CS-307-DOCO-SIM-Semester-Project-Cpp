#pragma once
#include "DocoMovePatternDefault.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternDefault::moveStrategy() {
	return moveDirs->getXYOffsets();	
}

std::vector<std::pair<int, int> > DocoMovePatternDefault::avoidanceStrategy() {
	// TODO: implement normal move avoidance pair options to select if others don't work.
}

DocoMovePatternDefault::DocoMovePatternDefault() {

}

DocoMovePatternDefault::~DocoMovePatternDefault() {

}