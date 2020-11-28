#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "Player.hpp"

/** the default KI-Player thinking about a best move */
class SimulatePlayer : public Player
{
protected:
    /** how deep the bot should search for the best move */
    int deep;

public:
    /** constructor */
    SimulatePlayer(int deep = 2);

    /** @inheritdoc */
     virtual int getMove(GameSettings & game);

     /** default setter */
     inline void setDeep(int deep) {this->deep = deep;}
};

#endif //PLAYER_SIMULATEPLAYER_HPP
