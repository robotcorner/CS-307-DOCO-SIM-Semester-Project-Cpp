#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternHorizontal :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

