#include "../../include/player/SimulatePlayer.hpp"
#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/GameSettings.hpp"
#include "../../include/minmax/Minmax.hpp"

SimulatePlayer::SimulatePlayer(int deep): Player(), deep(deep) {
}

int SimulatePlayer::getMove(GameSettings & game)
{
    MinMax minMax(game, this->id);
    std::vector<PossibleMove> moves = PossibleMove::calcPossibleMoves(game.currentMap, game, this->getId());
    int resultMoveIndex = 0;
    intMoveScore resultRating = 0;

    minMax.getMove(moves, resultMoveIndex, resultRating, -RATING_VICTORY, RATING_VICTORY, this->deep, this->id);

    std::cout << "Selected the " << (resultMoveIndex + 1) << "th, which is Column #" << (moves[resultMoveIndex].moveColumn + 1) << std::endl;
    return moves[resultMoveIndex].moveColumn;
}
