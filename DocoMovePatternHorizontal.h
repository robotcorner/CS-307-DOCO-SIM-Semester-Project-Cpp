#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternHorizontal :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
};

// TODO:	Behavior pattern 1 will cause the DOCO to move only in a horizontal direction. 
//          If an edge of the world is encountered the DOCO will randomly elect to move up
//          or down a row and reverse its direction of movement.

