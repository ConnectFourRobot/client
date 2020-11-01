#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "iostream"
#include "game/Game.hpp"

class GameHandler{
    private:
        short _playerNumber;
        Game _game;
    public:
        GameHandler();
        
        /**
         * starts the gamehandler
        */
        void run();
        ~GameHandler();
};
#endif