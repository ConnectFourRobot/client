#include "../../include/player/SimulatePlayer.hpp"
#include "../../include/game/GameSettings.hpp"
#include "../../include/minmax/Minmax.hpp"
#include "../../include/logger/Logger.hpp"

#include <cstdlib>
#include <ctime>

#define DEBUG_BEWERTUNGEN 1

SimulatePlayer::SimulatePlayer(int deep, int randomFactor): Player(), deep(deep), randomFactor(randomFactor) {
    srand(time(NULL));
}

int SimulatePlayer::getMove(GameSettings & game)
{
    int maxSecondPenalty = this->randomFactor - rand() % 1000;
    MinMax minMax(game, this->id, maxSecondPenalty <= 0);
    std::vector<PossibleMove> moves = PossibleMove::calcPossibleMoves(game.currentMap, game, this->getId());
    int resultMoveIndex = 0;
    intMoveScore resultRating = 0;

    minMax.getMove(moves, resultMoveIndex, resultRating, -RATING_VICTORY, RATING_VICTORY, this->depth, this->id);

    if (DEBUG_BEWERTUNGEN) {
        for (PossibleMove & move0 : moves) {
            LOG << "Bewertung Spalte #" << (move0.getMoveColumn() + 1) << " ist " << move0.getScore() << std::endl;
        }
    }

    // sometimes the bot chooses the second best move instead of the best move
    if (maxSecondPenalty > 0) {
        PossibleMove * secondMove = this->getSecondBestMove(moves, resultRating - maxSecondPenalty);
        if (secondMove != nullptr) {
            LOG << "Selected the second best move, which is Column #" << (secondMove->getMoveColumn() + 1)
            << "(maxSecondPenalty = " << maxSecondPenalty << ") " << std::endl;
            return secondMove->getMoveColumn();
        }
    }

    //TODO to logger
    LOG << "Selected the Column #" << (moves[resultMoveIndex].getMoveColumn() + 1)
    << "(maxSecondPenalty = " << maxSecondPenalty << ") " << std::endl;
    return moves[resultMoveIndex].getMoveColumn();
}

PossibleMove * SimulatePlayer::getSecondBestMove(std::vector<PossibleMove> & moves, intMoveScore minimumRating)
{
    intMoveScore bestRating = minimumRating;
    intMoveScore secondRating = minimumRating;
    intMoveScore currentScore;
    PossibleMove * bestMove = nullptr;
    PossibleMove * secondMove = nullptr;

    for (PossibleMove & move0 : moves) {
        currentScore = move0.getScore();
        if (currentScore > bestRating) {
            secondRating = bestRating;
            bestRating = currentScore;
            secondMove = bestMove;
            bestMove = &move0;
        } else if (currentScore > secondRating) {
            secondRating = currentScore;
            secondMove = &move0;
        }
    }
    return secondMove;
}
