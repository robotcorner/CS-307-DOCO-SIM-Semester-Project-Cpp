#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternDefault :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
};

