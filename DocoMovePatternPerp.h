#pragma once
#include "DocoMoveStrategy.h"
class DocoMovePatternPerp : public DocoMoveStrategy
{
private:
    std::vector<std::pair<int, int> > moveDirs;
public:
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
    DocoMovePatternPerp();
    ~DocoMovePatternPerp();
};

