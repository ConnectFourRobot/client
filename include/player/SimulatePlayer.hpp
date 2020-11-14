#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "Player.hpp"

class SimulatePlayer : public Player
{
public:
    /** constructor */
    SimulatePlayer();

    /** @inheritdoc */
     virtual int getMove(Game & game);
};

#endif //PLAYER_SIMULATEPLAYER_HPP
