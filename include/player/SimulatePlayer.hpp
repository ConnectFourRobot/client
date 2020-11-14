#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "Player.hpp"

class SimulatePlayer : public Player {
public:
    virtual int getMove(Game & game);
};

#endif //PLAYER_SIMULATEPLAYER_HPP
