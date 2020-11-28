#ifndef PLAYER_DEBUGPLAYER_HPP
#define PLAYER_DEBUGPLAYER_HPP

#include "Player.hpp"

class DebugPlayer : public Player
{
public:
    /** constructor */
    DebugPlayer(): Player() {}

    /** @inheritdoc */
    virtual int getMove(GameSettings & game);
};

#endif //PLAYER_DEBUGPLAYER_HPP
