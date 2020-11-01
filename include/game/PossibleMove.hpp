#ifndef POSSIBLEMOVE_HPP
#define POSSIBLEMOVE_HPP

#include "Grid.hpp"

class PossibleMove{
    public:
        PossibleMove(int move, Grid grid) : 
            Move(move), AfterGrid(grid){};
        PossibleMove() {};
        int Score;
        int Move = 0;
        Grid AfterGrid;
};
#endif