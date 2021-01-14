#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "../rating/RatingScore.hpp"
#include "../game/PossibleMove.hpp"

// extern included types
class GameSettings;

/** Handles MinMax-Algorithmus using Alpha-Beta-Pruning */
class MinMax {
private:
    /** the game containing settings */
    GameSettings & game;

    /** the KI-Player-id */
    int playerSelfId;

    /** enable pruning for speed up */
    bool enablePruning;

    /** evaluate the moves without going deeper
     * @param std::vector<self> & moves All move candidates for the best move
     * @param int & resultIndex (write-only) The index of the moves vector, which is determined to be the best move
     * @param intMoveScore & resultRating (write-only) The rating of the best move
     * @param intMoveScore pruningMinAlpha the alpha value of Alpha-Beta-Pruning-Algorithm
     * @param intMoveScore pruningMaxBeta the beta value of Alpha-Beta-Pruning-Algorithm
     * @param int playerTurnId The player's id who made the moves given in vector moves
     * @param bool isMaximizer true: best move is the one with highest rating. false: best move is the one with least rating.
     */
    inline void rateMoves(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int playerTurnId, bool isMaximizer);

    /** evaluate the moves by going deeper
     * @param std::vector<self> & moves All move candidates for the best move
     * @param int & resultIndex (write-only) The index of the moves vector, which is determined to be the best move
     * @param intMoveScore & resultRating (write-only) The rating of the best move
     * @param intMoveScore pruningMinAlpha the alpha value of Alpha-Beta-Pruning-Algorithm
     * @param intMoveScore pruningMaxBeta the beta value of Alpha-Beta-Pruning-Algorithm
     * @param int playerTurnId The player's id who made the moves given in vector moves
     * @param bool isMaximizer true: best move is the one with highest rating. false: best move is the one with least rating.
     */
    void getMoveDeeper(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int deep, int playerTurnId, bool isMaximizer);

    /** evaluate the score of a move and decide if cut-off-able
     * @param PossibleMove & mov The move which should be evaluated
     * @param int i The index of the mov in its vector moves
     * @param int & resultIndex (read-write) The index of the best move so far
     * @param intMoveScore & resultRating (read-write) The rating of the best move so far
     * @param intMoveScore & pruningMinAlpha (read-write) the alpha value of Alpha-Beta-Pruning-Algorithm so far
     * @param intMoveScore & pruningMaxBeta (read-write) the beta value of Alpha-Beta-Pruning-Algorithm so far
     * @param bool isMaximizer
     * @return bool perform cut-off */
    bool evaluateScore(PossibleMove & mov, int i, int & resultIndex, intMoveScore & resultRating, intMoveScore & pruningMinAlpha, intMoveScore & pruningMaxBeta, bool isMaximizer);

public:
    /** default constructor */
    MinMax(GameSettings & game, int playerSelfId, bool enablePruning);

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
