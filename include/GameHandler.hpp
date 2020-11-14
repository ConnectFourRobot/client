#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>

#include <iostream>
#include "game/Game.hpp"
#include "network/DataHandlingService.hpp"

class GameHandler
{
private:
    short _playerNumber;
    Game _game;
public:
    /** constructor */
    GameHandler(std::string host, unsigned short port);

    /** destructor */
    ~GameHandler();

    /**
     * starts the gamehandler
    */
    void run();
};
#endif
