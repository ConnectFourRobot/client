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
    /**
    * evaluation of the move done here
    */
    int score;

    /**
    * The move done here
    */
    const int moveColumn;

    /**
    * The grid after the move is done
    */
    Grid afterGrid;

    /**
     * Get all moves that are possible
     *
     * @param Grid & oldGrid on which this should be calculated
     * @param Game & according Game
     * @param int playerId The player whose turn it is.
     * @return std::vector<PossibleMove> possible moves
    */
    static std::vector<PossibleMove> calcPossibleMoves(Grid & oldGrid, Game & game, int playerId);
};
#endif
