#include "../../include/player/SimulatePlayer.hpp"
#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/GameSettings.hpp"
#include "../../include/minmax/Minmax.hpp"

SimulatePlayer::SimulatePlayer(int depth): Player(), depth(depth) {
}

int SimulatePlayer::getMove(GameSettings & game)
{
    MinMax minMax(game, this->id);
    std::vector<PossibleMove> moves = PossibleMove::calcPossibleMoves(game.currentMap, game, this->getId());
    int resultMoveIndex = 0;
    intMoveScore resultRating = 0;

    minMax.getMove(moves, resultMoveIndex, resultRating, -RATING_VICTORY, RATING_VICTORY, this->depth, this->id);

    //TODO to logger
    std::cout << "Selected the " << (resultMoveIndex + 1) << "th, which is Column #" << (moves[resultMoveIndex].getMoveColumn() + 1) << std::endl;
    return moves[resultMoveIndex].getMoveColumn();
}
