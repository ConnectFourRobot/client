#include "../../include/minmax/Minmax.hpp"
#include "../../include/rating/Rating.hpp"

MinMax::MinMax(GameSettings & game, int playerSelfId, bool enablePruning): game(game), playerSelfId(playerSelfId), enablePruning(enablePruning)
{
}

void MinMax::getMove(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int depth, int playerTurnId)
//void MinMax::getMove(Grid & grid, int & resultMove, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int depth, int playerTurnId)
{
    bool isMaximizer = (playerTurnId == this->playerSelfId);
    resultRating = ((isMaximizer) ? -(RATING_VICTORY + 1000) : (RATING_VICTORY + 1000));

    if (depth <= 0)
    {
        this->rateMoves(moves, resultIndex, resultRating, pruningMinAlpha, pruningMaxBeta, playerTurnId, isMaximizer);
    }
    else
    {
        this->getMoveDeeper(moves, resultIndex, resultRating, pruningMinAlpha, pruningMaxBeta, depth, playerTurnId, isMaximizer);
    }
}

inline void MinMax::rateMoves(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int playerTurnId, bool isMaximizer)
{
    int countMoves = moves.size(), i;
    Rating rating(this->game, this->playerSelfId, 0);

    for (i = 0; i < countMoves; i++)
    {
        PossibleMove & mov = moves[i];
        mov.setScore(rating.rate(mov.getAfterGrid()));
        if (this->evaluateScore(mov, i, resultIndex, resultRating, pruningMinAlpha, pruningMaxBeta, isMaximizer))
        {
            // cut off because of pruning
            if (this->enablePruning) return;
        }
    }
}

void MinMax::getMoveDeeper(std::vector<PossibleMove> & moves, int & resultIndex, intMoveScore & resultRating, intMoveScore pruningMinAlpha, intMoveScore pruningMaxBeta, int depth, int playerTurnId, bool isMaximizer)
{
    int countMoves = moves.size(), i = 0, subMovIndex = 0, otherPlayerTurnId = otherPlayer(playerTurnId);
    intMoveScore subScore = 0;
    depth--;

    for (i = 0; i < countMoves; i++)
    {
        PossibleMove & mov = moves[i];
        if (mov.getAfterGrid().isMovePossible())
        {
            std::vector<PossibleMove> subMoves = PossibleMove::calcPossibleMoves(mov.getAfterGrid(), this->game, otherPlayerTurnId);
            this->getMove(subMoves, subMovIndex, subScore, pruningMinAlpha, pruningMaxBeta, depth, otherPlayerTurnId);
            mov.setScore(subScore);
        }
        else     //mov is not playable
        {
            Rating rating(this->game, this->playerSelfId, depth + 1);
            mov.setScore(rating.rate(mov.getAfterGrid()));
        }
        if (this->evaluateScore(mov, i, resultIndex, resultRating, pruningMinAlpha, pruningMaxBeta, isMaximizer))
        {
            // cut off because of pruning
            if (this->enablePruning) return;
        }
    }
}


/**
 * @return bool can we cut off remaining moves because of pruning
 */
bool MinMax::evaluateScore(PossibleMove & mov, int i, int & resultIndex, intMoveScore & resultRating, intMoveScore & pruningMinAlpha, intMoveScore & pruningMaxBeta, bool isMaximizer)
{
    intMoveScore subScore = mov.getScore();
    if (isMaximizer && subScore > resultRating)
    {
        resultRating = subScore;
        resultIndex = i;
        if (subScore > pruningMinAlpha)
        {
            pruningMinAlpha = subScore;
        }
        return (subScore >= pruningMaxBeta);
    }
    else if ((!isMaximizer) && subScore < resultRating)
    {
        resultRating = subScore;
        resultIndex = i;
        if (subScore < pruningMaxBeta)
        {
            pruningMaxBeta = subScore;
        }
        return (subScore <= pruningMinAlpha);
    }
    else
    {
        return false;
    }
}
