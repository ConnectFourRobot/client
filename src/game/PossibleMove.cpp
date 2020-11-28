#include "../../include/game/PossibleMove.hpp"
#include "../../include/game/Grid.hpp"
#include "../../include/game/GameSettings.hpp"

PossibleMove::PossibleMove(const Grid & oldGrid, int column, int playerId) : _score(0), _moveColumn(column), _afterGrid(oldGrid)
{
    this->_afterGrid.putStone(playerId, column);
};

std::vector<PossibleMove> PossibleMove::calcPossibleMoves(Grid & oldGrid, GameSettings & game, int playerId)
{
    std::vector<PossibleMove> result;
    result.reserve(game.sizeX);

    for (int x = 0; x < game.sizeX; ++x)
    {
        if (oldGrid.isMovePossible() && !(oldGrid.isColumnFull(x)))
        {
            result.push_back(PossibleMove(oldGrid, x, playerId));
        }
    }

    return result;
}
