#include "../../include/player/SimulatePlayer.hpp"
#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/Game.hpp"

int SimulatePlayer::getMove(Game & game)
{
    std::vector<PossibleMove> moves = PossibleMove::calcPossibleMoves(game.currentMap, game, this->getId());
    int countMoves = moves.size();
    int resultMoveIndex = rand() % countMoves;

    std::cout << "Found " << countMoves << " Moves. Selected the " << (resultMoveIndex + 1) << "th, which is Column #" << (moves[resultMoveIndex].moveColumn + 1) << std::endl;
    return moves[resultMoveIndex].moveColumn;
}
