#ifndef RATING_HPP
#define RATING_HPP

#include "RatingScore.hpp"
class Game;
class Grid;

class Rating {
private:
    Game & game;
    intMoveScore ratePlayable(Grid & grid);
    intMoveScore rateFinished(Grid & grid);

public:
    Rating(Game & game);
    intMoveScore rate(Grid & grid);
};

#endif // RATING_HPP
