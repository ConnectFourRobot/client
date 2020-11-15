#include "../../include/minmax/Minmax.hpp"

MinMax::MinMax(Game & game): game(game)
{
}

void MinMax::getMove(std::vector<PossibleMove> moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int deep, int playerId)
{
    if (deep <= 0) {
        this->rateMoves(moves, resultIndex, resultRating, pruningMinAlpha, pruningMaxBeta);
    }

    int countMoves = moves.size();
    for (PossibleMove & mov : moves) {

    }

}

void MinMax::rateMoves(std::vector<PossibleMove> moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta) {
    for (PossibleMove & mov : moves) {


    }

}
