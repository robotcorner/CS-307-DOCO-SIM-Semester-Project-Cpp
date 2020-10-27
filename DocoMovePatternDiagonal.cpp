#pragma once
#include "DocoMovePatternDiagonal.h"
#include <vector>
#include "Directions.h"

// Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.

Directions* moveDirs = new Directions();


// --- This is the default move strategy
std::vector<std::pair<int, int> > DocoMovePatternDiagonal::moveStrategy() {
	return moveDirs->getDiagonalPairOffsets();	
}

// If an edge of the world is encountered the DOCO will randomly elect to move 
// left, right, up, or down and either reverse its direction of movement or move
// in the other diagonal direction.

// --- This is the strategy for when the default fails, ie: docos / obstacles prevent movement
std::vector<std::pair<int, int> > DocoMovePatternDiagonal::avoidanceStrategy() {
	// TODO: implement avoidance strategy for diagonal move pattern
	//	     If an edge of the world is encountered the DOCO will randomly elect to (move 
	//       left, right, up, or down) and either (reverse its direction of movement) or (move
	//       in the other diagonal direction.)
	// X => +
	// 
	//	a      c  
	//	 x    x
	//    b  d
	// 
	//	a	c
	//	  x
	//  d   b

//a x b    go a, reverse is b    go b reverse is a   the other diagonal direction(line) from c x d      Line1
//c x d    go c, reverse is d    go d reverse is c   the other diagonal direction(line) from a x b      Line2
//
// Reverse only works on a line not all diagonals


	return moveDirs->getPerpPairOffsets();
}

DocoMovePatternDiagonal::DocoMovePatternDiagonal() {

}

DocoMovePatternDiagonal::~DocoMovePatternDiagonal() {

}

