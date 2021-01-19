#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "Player.hpp"

/** the default KI-Player thinking about a best move */
class SimulatePlayer : public Player
{
protected:
    /** how deep the bot should search for the best move */
    int depth;

public:
    /** constructor */
    SimulatePlayer(int depth = 2);

    /** @inheritdoc */
     virtual int getMove(GameSettings & game);

     /** default setter */
     inline void setDepth(int depth) {this->depth = depth;}
};

#endif //PLAYER_SIMULATEPLAYER_HPP
