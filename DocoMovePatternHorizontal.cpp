#pragma once
#include "DocoMovePatternHorizontal.h"
#include <vector>
#include "Directions.h"

Directions* moveDirs = new Directions();

std::vector<std::pair<int, int> > DocoMovePatternHorizontal::moveStrategy() {
// if vectors in (CellGrid::findAdjoinedCellsFood()) then random pick a vector	   //FOOD FIRST
// else {if current direction is (not in findAdjoinedCells) or (in CellGrid::findAdjoinedOccupiedCells()) then reverse direction;  //HIT WALL or DOCO(REVERSE)
//      if direction is a vector in (getHorizontalPairOffsetsWithDir()and findAdjoinedCells ) and 
//        not in  (CellGrid::findAdjoinedObstacleCells() and  CellGrid::findAdjoinedOccupiedCells())   then pick it  //NO WALL, DOCO, OBSTACLE
//     }
// AVOIDENCE Need to sidestep for avoidence, Random Pick possible directions if any. //GO VERTICAL
// else if  vectors from  (getVerticalPairOffsetsWithDir() in findAdjoinedCells ) and not in
//      (CellGrid::findAdjoinedObstacleCells() and  CellGrid::findAdjoinedOccupiedCells()) pick random vector
	
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