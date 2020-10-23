#pragma once
#include "DocoMoveStrategy.h"
#include <string>
class DocoMovePatternDiagonal : public DocoMoveStrategy
{
private:
    std::string strategy = "Diagonal";
public:
    std::vector<std::pair<int, int> > moveStrategy();
    std::vector<std::pair<int, int> > avoidanceStrategy();
    std::string getStrategy();
};

// TODO:    Behavior pattern 3 will cause the DOCO to move only in a diagonal direction.
//          If an edge of the world is encountered the DOCO will randomly elect to move 
//          left, right, up, or down and either reverse its direction of movement or move
//          in the other diagonal direction.