#ifndef PLAYER_RANDOMMOVEPLAYER_HPP
#define PLAYER_RANDOMMOVEPLAYER_HPP

#include "Player.hpp"

/** a player using a random valid move each time */
class RandomMovePlayer : public Player
{
public:
    /** constructor */
    RandomMovePlayer();

    /** @inheritdoc */
    virtual int getMove(GameSettings & game);
};

#endif //PLAYER_RANDOMMOVEPLAYER_HPP
