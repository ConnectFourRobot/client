#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "../rating/RatingScore.hpp"
#include "../game/PossibleMove.hpp"

class Game;

class MinMax {
private:
    Game & game;

    void rateMoves(std::vector<PossibleMove> moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta);
public:
    MinMax(Game & game);
    void getMove(std::vector<PossibleMove> moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int deep, int playerId);
};

#endif // MINMAX_HPP
