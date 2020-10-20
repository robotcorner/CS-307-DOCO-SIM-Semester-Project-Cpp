#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternDiagonal : 
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

// TODO:    Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.
//          If an edge of the world is encountered the DOCO will randomly elect to move 
//          left, right, up, or down and either reverse its direction of movement or move
//          in the other diagonal direction.