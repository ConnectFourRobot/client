#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>

#include <iostream>
#include "game/GameSettings.hpp"
#include "network/DataHandlingService.hpp"

/** main class */
class GameHandler
{
private:
    short _playerNumber;
    GameSettings _game;

    void runRequest(void);
    void runMove(int column, int playerId);
public:
    /** constructor */
    GameHandler(std::string host, unsigned short port, int rows, int columns, int playerId, int level);

    /** destructor */
    ~GameHandler();

    /**
     * starts the gamehandler
    */
    void run(void);
    void runDebug(void);
};
#endif
