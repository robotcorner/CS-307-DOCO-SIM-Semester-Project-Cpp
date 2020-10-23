#pragma once
#include "DocoMoveStrategy.h"
#include <string>
class DocoMovePatternDefault : public DocoMoveStrategy
{
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
    DocoMovePatternDefault();
    ~DocoMovePatternDefault();
};

