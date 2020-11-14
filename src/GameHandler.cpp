#include "../include/GameHandler.hpp"
#include "../include/player/DebugPlayer.hpp"
#include "../include/player/RandomMovePlayer.hpp"
#include "../include/player/SimulatePlayer.hpp"

GameHandler::GameHandler(std::string host, unsigned short port): _game(7, 6)
{
    // ToDo: connect to broker
    if(DataHandlingService::getInstance().start(host, port) < 0)
    {
        //cannot connect to the server
        // ToDo: Log-Tool
        std::cout << "Cannot connect to broker" << std::endl;
        exit(0);
    }
    std::cout << "Init vgr-client" << std::endl;
}

void GameHandler::run()
{
    int gameMove;
    int winner;
    std::cout << "Run vgr-client" << std::endl;
    std::cout << "Compiled from " << __cplusplus << " at " __DATE__ << " - " << __TIME__ << std::endl;
    std::cout << "Playing on Map[" << this->_game.currentMap.mapArray.size() << "][" << this->_game.currentMap.mapArray[0].size() << "]" << std::endl;

    // Just for testing purposes!!!
    this->_game.addPlayer(new RandomMovePlayer());
    this->_game.addPlayer(new RandomMovePlayer());

    this->_playerNumber = 1;

    while(this->_game.currentMap.isPlayable())
    {
        // print current grid
        std::cout << this->_game.currentMap;

        //ask player for move
        gameMove = this->_game.getCurrentPlayer().getMove(this->_game);

        //validate Move

        //execute Move
        this->_game.putStone(gameMove);
    }


    std::cout << std::endl << "Game ended. ";
    winner = this->_game.currentMap.getWinner();
    if (winner < 0)
    {
        std::cout << "It is a draw. ";
    }
    else
    {
        std::cout << "Player #" << winner << " won. ";
    }
    std::cout << "Final grid: " << std::endl << this->_game.currentMap << std::endl;
}
