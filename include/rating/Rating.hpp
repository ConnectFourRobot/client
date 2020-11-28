#ifndef RATING_HPP
#define RATING_HPP

#include "RatingScore.hpp"

// extern included types
class GameSettings;
class Grid;

/** evaluation of a grid into a intMoveScore */
class Rating {
private:
    /** The settings of the game */
    const GameSettings & game;

    /** evaluate a game which will be continued later */
    intMoveScore ratePlayable(Grid & grid);

    /** evaluate a terminated game */
    intMoveScore rateFinished(Grid & grid);

    /** evaluate for which player */
    int playerSelfId;

    /** for terminated games: how many steps are skipped due to termination of game */
    int remainingDeep;
public:
    /** constructor */
    Rating(GameSettings & game, int playerSelfId, int remainingDeep);

    /** evaluate the grid */
    intMoveScore rate(Grid & grid);
};

#endif // RATING_HPP
