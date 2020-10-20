#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternVertical :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

