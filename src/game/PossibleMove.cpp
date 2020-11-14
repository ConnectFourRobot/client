#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/Grid.hpp"
#include "../../include/game/Game.hpp"

PossibleMove::PossibleMove(std::shared_ptr<PossibleMove> next, const Grid & oldGrid, int column, int playerId) :
    next(next), afterGrid(oldGrid), moveColumn(column)
{
    this->afterGrid.putStone(playerId, column);
};

std::shared_ptr<PossibleMove> PossibleMove::calcPossibleMoves(Grid & oldGrid, Game & game, int playerId)
{
    std::shared_ptr<PossibleMove> result = 0;
    for (int x = game.sizeX - 1; x >= 0; --x)
    {
        if (oldGrid.isPlayable() && oldGrid.isColumnNotFull(x))
        {
            result = std::shared_ptr<PossibleMove>(new PossibleMove(result, oldGrid, x, playerId));
        }
    }

    return result;
}
