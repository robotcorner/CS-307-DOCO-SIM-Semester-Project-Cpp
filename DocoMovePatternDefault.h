#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatterDefault :
    public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
};

