#pragma once
#include "DocoMoveStrategy.h"
#include <string>

// Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.

class DocoMovePatternDiagonal : public DocoMoveStrategy
{
public:
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
    DocoMovePatternDiagonal();
    ~DocoMovePatternDiagonal();
};

