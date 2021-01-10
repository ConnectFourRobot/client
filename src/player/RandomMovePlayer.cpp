#include "../../include/player/RandomMovePlayer.hpp"
#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/GameSettings.hpp"
#include "../../include/logger/Logger.hpp"

#include <cstdlib>
#include <ctime>

RandomMovePlayer::RandomMovePlayer(): Player()
{
    srand(time(NULL));
}

int RandomMovePlayer::getMove(GameSettings & game)
{
    auto moves = PossibleMove::calcPossibleMoves(game.currentMap, game, this->getId());
    int countMoves = moves.size();
    int resultMoveIndex = rand() % countMoves;

    //TODO to logger
    LOG << "Found " << countMoves << " Moves. Selected the " << (resultMoveIndex + 1) << "th, which is Column #" << (moves[resultMoveIndex].getMoveColumn() + 1) << std::endl;
    return moves[resultMoveIndex].getMoveColumn();
}
