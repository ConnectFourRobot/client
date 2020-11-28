#include "../../include/rating/Rating.hpp"
#include "../../include/rating/RatingCounter.hpp"
#include "../../include/game/GameSettings.hpp"
#include "../../include/game/Grid.hpp"

#define minMacro(a, b) (((a) < (b)) ? (a) : (b))
#define maxMacro(a, b) (((a) > (b)) ? (a) : (b))

Rating::Rating(GameSettings & game, int playerSelfId, int remainingDeep): game(game), playerSelfId(playerSelfId), remainingDeep(remainingDeep)
{
}

intMoveScore Rating::rate(const Grid & grid)
{
    if (grid.isMovePossible())
    {
        return this->ratePlayable(grid);
    }
    else
    {
        return this->rateFinished(grid);
    }
}

intMoveScore Rating::ratePlayable(const Grid & grid)
{
    int halfX, x, y, toX, toY, toY2;
    RatingCounter counter(playerSelfId);

    //horizontal
    for (y = 0; y < game.sizeY; y++)
    {
        for (x = 0; x < game.sizeX; x++)
        {
            counter.add(grid.getStoneSafe(x, y));
        }
        counter.nextBlock();
    }

    //vertical
    for (x = 0; x < game.sizeX; x++)
    {
        for (y = 0; y < game.sizeY; y++)
        {
            counter.add(grid.getStoneSafe(x, y));
        }
        counter.nextBlock();
    }

    //diagonal
    for (halfX = 0; halfX < 2; halfX++)
    {
        //descending diagonal
        toX = (game.sizeX + game.sizeY - 3) / 2;
        for (x = 2 - halfX; x <= toX; x++)
        {
            toY = game.sizeX - x;
            toY2 = x + halfX + 1;
            toY = minMacro(toY, toY2);
            y = x + 1 - game.sizeY + halfX;
            for (y = maxMacro(-x, y); y < toY; y++)
            {
                counter.add(grid.getStoneSafe(x + y, x - y + halfX));
            }
            counter.nextBlock();
        }

        //ascending diagonal
        toX = (game.sizeX + halfX - 3) / 2;
        for (x = (halfX - game.sizeY + 4) / 2; x < toX; x++) {
            toY = game.sizeX - x;
            toY2 = game.sizeY + x - halfX;
            toY = minMacro(toY, toY2);
            y = x - halfX;
            for (y = maxMacro(-x, y); y < toY; y++)
            {
                counter.add(grid.getStoneSafe(y + x, y - x + halfX));
            }
            counter.nextBlock();
        }
    }
    return counter.getScoreAndReset();
}

intMoveScore Rating::rateFinished(const Grid & grid)
{
    int winner = grid.getWinner();
    if (winner < 0) {
        //it is a draw
        return 0;
    } else if (winner == this->playerSelfId) {
        //player 1 won
        return RATING_VICTORY + this->remainingDeep;
    } else {
        //player 2 won
        return -RATING_VICTORY - this->remainingDeep;
    }
}
