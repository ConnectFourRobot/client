#ifndef PLAYER_NETWORKPLAYER_HPP
#define PLAYER_NETWORKPLAYER_HPP

#include "Player.hpp"

class NetworkPlayer : public Player
{
public:
    /** constructor */
    NetworkPlayer() : Player() {}

    /** @inheritdoc */
    virtual int getMove(GameSettings & game)
    {
        //errorlog
        throw "NetworkPlayer must not be asked for move";
        return 0;
    }
};

#endif //PLAYER_NETWORKPLAYER_HPP
