#ifndef PLAYER_RANDOMMOVEPLAYER_HPP
#define PLAYER_RANDOMMOVEPLAYER_HPP

#include "Player.hpp"

class RandomMovePlayer : public Player {
public:
    RandomMovePlayer();
    virtual int getMove(Game & game);
};

#endif //PLAYER_RANDOMMOVEPLAYER_HPP
