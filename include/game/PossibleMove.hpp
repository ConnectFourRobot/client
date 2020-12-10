#ifndef POSSIBLEMOVE_HPP
#define POSSIBLEMOVE_HPP

#include "Grid.hpp"

class PossibleMove{
    public:
        PossibleMove(int move, Grid grid) :
            move(move), afterGrid(grid){};
        PossibleMove() {};
        int score;
        int move = 0;
        Grid afterGrid;
};
#endif
