#ifndef POSSIBLEMOVE_HPP
#define POSSIBLEMOVE_HPP

#include <memory>
#include "Grid.hpp"
class Game;
class PossibleMove
{
private:
    PossibleMove(std::shared_ptr<PossibleMove> next, const Grid & oldGrid, int column, int playerId);
public:
    int score;
    const int moveColumn;
    Grid afterGrid;
    std::shared_ptr<PossibleMove> next;
    static std::shared_ptr<PossibleMove> calcPossibleMoves(Grid & oldGrid, Game & game, int playerId);
};
#endif
