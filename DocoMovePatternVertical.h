#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternVertical :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

//	TODO:   Behavior pattern 2 will cause the DOCO to move only in a vertical direction.
//          If an edge of the world is encountered the DOCO will randomly elect to move 
//          left or right a column and reverse its direction of movement.