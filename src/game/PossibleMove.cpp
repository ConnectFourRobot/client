#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/Grid.hpp"
#include "../../include/game/Game.hpp"

PossibleMove::PossibleMove(const Grid & oldGrid, int column, int playerId) : afterGrid(oldGrid), moveColumn(column)
{
    this->afterGrid.putStone(playerId, column);
};

std::vector<PossibleMove> PossibleMove::calcPossibleMoves(Grid & oldGrid, Game & game, int playerId)
{
    std::vector<PossibleMove> result;
    result.reserve(game.sizeX);

    for (int x = 0; x < game.sizeX; ++x)
    {
        if (oldGrid.isPlayable() && oldGrid.isColumnNotFull(x))
        {
            result.push_back(PossibleMove(oldGrid, x, playerId));
        }
    }

    return result;
}
