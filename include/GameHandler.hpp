#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>

#include <iostream>
#include "game/Game.hpp"
#include "network/DataHandlingService.hpp"

class GameHandler{
    private:
        short _playerNumber;
        Game _game;
    public:
        GameHandler(std::string host, unsigned short port);
        
        /**
         * starts the gamehandler
        */
        void run();
        ~GameHandler();
};
#endif