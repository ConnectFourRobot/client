#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "../rating/RatingScore.hpp"
#include "../game/PossibleMove.hpp"

class Game;

class MinMax {
private:
    /** the game containing settings */
    Game & game;

    /** evaluate the moves without going deeper */
    inline void rateMoves(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int playerTurnId, bool isMaximizer);

    /** evaluate the moves by going deeper */
    void getMoveDeeper(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int deep, int playerTurnId, bool isMaximizer);

    /** evaluate the score of a move
     * @return bool perform cut-off */
    bool evaluateScore(PossibleMove & mov, int i, int & resultIndex, intMoveScore & resultRating, intMoveScore & pruningMinAlpha, intMoveScore & pruningMaxBeta, bool isMaximizer);

    /** the KI-Player-id */
    int playerSelfId;
public:
    /** default constructor */
    MinMax(Game & game, int playerSelfId);

    /** search the best move
    * @param std::vector<PossibleMove> & moves A list of all possible Moves
    * @param int & resultIndex (return-value) The index of the moves vector, which is the best move
    * @param intMoveScore & resultRating The rating of the best move
    * @param intMoveScore pruningMinAlpha Pruning value Alpha, should be initialized with -RATING_VICTORY
    * @param intMoveScore pruningMaxBeta Pruning value Beta, should be initialized with +RATING_VICTORY
    * @param int deep search deepness: 0=only evaluate these given moves, 1=only evaluate these moves and the responses, ...
    * @param int playerTurnId The player who has made the moves in the vector moves
    * @param int playerSelfId The KI player
    */
    void getMove(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int deep, int playerTurnId);
};

#endif // MINMAX_HPP
