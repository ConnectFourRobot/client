#include "../../include/rating/Rating.hpp"
#include "../../include/rating/RatingCounter.hpp"
#include "../../include/game/Game.hpp"
#include "../../include/game/Grid.hpp"

#define minMacro(a, b) (((a) < (b)) ? (a) : (b))
#define maxMacro(a, b) (((a) > (b)) ? (a) : (b))

Rating::Rating(Game & game): game(game)
{
}

intMoveScore Rating::rate(Grid & grid)
{
    if (grid.isPlayable())
    {
        return this->ratePlayable(grid);
    }
    else
    {
        return this->rateFinished(grid);
    }
}

intMoveScore Rating::ratePlayable(Grid & grid)
{
    int halfX, x, y, toX, toY, toY2;
    RatingCounter counter;

    //horizontal
    for (y = 0; y < game.sizeY; y++)
    {
        for (x = 0; x < game.sizeX; x++)
        {
            counter.add(grid.getStone(x, y));
        }
        counter.nextBlock();
    }

    //vertical
    for (x = 0; x < game.sizeX; x++)
    {
        for (y = 0; y < game.sizeY; y++)
        {
            counter.add(grid.getStone(x, y));
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
                counter.add(grid.getStone(x + y, x - y + halfX));
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
                counter.add(grid.getStone(y + x, y - x + halfX));
            }
            counter.nextBlock();
        }
    }
    return counter.getScoreAndReset();
}

intMoveScore Rating::rateFinished(Grid & grid)
{
    if (grid.stateOfGame & GAMESTATE_WIN_BIT)
    {
        return ((grid.stateOfGame & GAMESTATE_PLAYERID_MASK == 1) ? RATING_VICTORY : -RATING_VICTORY);
    }
    return 0;
}
