#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternDiagonal : 
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

