#ifndef POSSIBLEMOVE_HPP
#define POSSIBLEMOVE_HPP

#include <vector>
#include "Grid.hpp"
#include "../rating/RatingScore.hpp"

// extern included types
class GameSettings;

/** a single possible move */
class PossibleMove
{
private:
    /** constructor
     * executes the move and stores the new grid
     * @param const Grid & oldGrid the grid, into which a stone will be inserted
     * @param int column the column-id into which a stone will be inserted (0 - sizeX-1)
     * @param int playerId (1-2) */
    PossibleMove(const Grid & oldGrid, int column, int playerId);

public:
    /**
    * evaluation of the move done here
    */
    intMoveScore score;

    /**
    * The move done here (0 - sizeX-1)
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
    static std::vector<PossibleMove> calcPossibleMoves(Grid & oldGrid, GameSettings & game, int playerId);

    /** default getter for score */
    inline intMoveScore getScore() {return this->score;}

    /** default setter for score */
    inline void setScore(intMoveScore score) {this->score = score;}
};
#endif
