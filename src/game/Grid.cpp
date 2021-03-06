#include "../../include/game/Grid.hpp"

/** constructor */
Grid::Grid(int sizeX, int sizeY):
    //initializer
    mapArray(std::vector<std::vector<uint8_t>>(sizeY, std::vector<uint8_t>(sizeX, 0))),
    stateOfGame(GAMESTATE_RUNNING_BIT)
{
}

/** copy-constructor */
Grid::Grid(const Grid& grid):
    mapArray(grid.mapArray),
    stateOfGame(grid.stateOfGame)
{
}

uint8_t Grid::getStoneSafe(int x, int y) const
{
    if (x < 0 || y < 0 || y >= static_cast<int>(this->mapArray.size()))
    {
        return 255;
    }
    const std::vector<uint8_t> & mapLine = this->mapArray[y];
    if (x >= static_cast<int>(mapLine.size()))
    {
        return 255;
    }
    return mapLine[x];
}

bool Grid::isColumnFull(int x)
{
    return this->getStone(x, 0) != 0;
}

int Grid::getWinner(void) const
{
    if (this->stateOfGame & GAMESTATE_WIN_BIT)
    {
        return static_cast<int>(this->stateOfGame & GAMESTATE_PLAYERID_MASK);
    }
    else
    {
        return -1;
    }
}

bool Grid::putStone(int playerId, int column)
{
    int freeRow = this->freeRow(column);
    if (!this->isMovePossible() || freeRow < 0)
    {
        //TODO log
        return false;
    }
    this->getStone(column, freeRow) = playerId;
    this->evaluateStone(column, freeRow, playerId);
    return true;
}

inline void Grid::evaluateStone(int column, int row, int playerId)
{
    int countStones, x, y;

    //all 4 direction-pairs
    int vertical[] = {0, 1};
    int horizontal[] = {1, 0};
    int diagonalAsc[] = {-1, 1};
    int diagonalDesc[] = {1, 1};
    int * diffDirections[5] = {vertical, horizontal, diagonalAsc, diagonalDesc, 0};
    int * diffDirection = 0;

    //check for victoy
    for(int di = 0; di < 4; ++di)
    {
        diffDirection = diffDirections[di];
        x = column + diffDirection[0];
        y = row + diffDirection[1];
        countStones = 1;
        while(this->getStoneSafe(x, y) == playerId)
        {
            countStones++;
            x += diffDirection[0];
            y += diffDirection[1];
        }
        x = column - diffDirection[0];
        y = row - diffDirection[1];
        while(this->getStoneSafe(x, y) == playerId)
        {
            countStones++;
            x -= diffDirection[0];
            y -= diffDirection[1];
        }
        if (countStones >= 4)
        {
            // The player won the game
            // remove running bit, remove playerId-area
            this->stateOfGame &= ~(GAMESTATE_RUNNING_BIT | GAMESTATE_PLAYERID_MASK);

            // set win bit and playerId of winner
            this->stateOfGame |= GAMESTATE_WIN_BIT | (playerId & GAMESTATE_PLAYERID_MASK);

            return;
        }
    }

    //check, if game is full and a draw
    if (row == 0)
    {
        for (x = this->mapArray.size() - 1; x >= 0; x++)
        {
            if (!(this->isColumnFull(x)))
            {
                return;
            }
        }
        this->stateOfGame &= ~GAMESTATE_RUNNING_BIT;
    }

}

int Grid::freeRow(int x)
{
    int sizeY = mapArray.size();
    for (int y = 0; y < sizeY; y++)
    {
        if (this->getStone(x, y) != 0)
        {
            return y - 1;
        }
    }
    return sizeY - 1;
}

/**
 * Prints the mapArray
*/
std::ostream& operator << (std::ostream &out, const Grid &g)
{
    for(std::vector<uint8_t> iv : g.mapArray)
    {
        for(uint8_t i : iv)
        {
            out << static_cast<int>(i) << " ";
        }
        out << std::endl;
    }
    return out;
}
