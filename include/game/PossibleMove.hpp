#ifndef POSSIBLEMOVE_HPP
#define POSSIBLEMOVE_HPP

#include <vector>
#include "Grid.hpp"
class Game;
class PossibleMove
{
private:
    PossibleMove(const Grid & oldGrid, int column, int playerId);
public:
    int score;
    const int moveColumn;
    Grid afterGrid;

    int countMoves() const;

    static std::vector<PossibleMove> calcPossibleMoves(Grid & oldGrid, Game & game, int playerId);
};
#endif
