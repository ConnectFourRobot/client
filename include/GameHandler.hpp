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

    /** a move request has been received from network */
    inline void runRequest(void);

    /** after initialization, the client must register to the broker */
    inline void runRegisterClientAtBroker(void);

    /** a move action has been received from broker
     * @param int column a stone has been inserted into this column (0 - sizeX-1)
     * @param int playerId this playerId has inserted a stone (1 - 2)
    */
    inline void runMove(int column, int playerId);

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
