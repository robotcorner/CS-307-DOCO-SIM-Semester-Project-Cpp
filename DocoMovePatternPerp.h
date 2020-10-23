#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternPerp : public DocoMoveStrategy
{
public:
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
};

