#ifndef RATING_HPP
#define RATING_HPP

#include "RatingScore.hpp"
class GameSettings;
class Grid;

class Rating {
private:
    GameSettings & game;
    intMoveScore ratePlayable(Grid & grid);
    intMoveScore rateFinished(Grid & grid);
    int playerSelfId;
    int remainingDeep;
public:
    Rating(GameSettings & game, int playerSelfId, int remainingDeep);
    intMoveScore rate(Grid & grid);
};

#endif // RATING_HPP
