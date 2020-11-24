#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "Player.hpp"

class SimulatePlayer : public Player
{
protected:
    int deep;

public:
    /** constructor */
    SimulatePlayer(int deep = 2);

    /** @inheritdoc */
     virtual int getMove(Game & game);

     /** default setter */
     inline void setDeep(int deep) {this->deep = deep;}
};

#endif //PLAYER_SIMULATEPLAYER_HPP
