#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternPerp :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

