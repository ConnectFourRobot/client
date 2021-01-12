#include "../include/GameHandler.hpp"
#include "../include/player/DebugPlayer.hpp"
#include "../include/player/RandomMovePlayer.hpp"
#include "../include/player/SimulatePlayer.hpp"
#include "../include/player/NetworkPlayer.hpp"
#include "../include/logger/Logger.hpp"

//TODO delete these tests
#include "../include/rating/Rating.hpp"

GameHandler::GameHandler(std::string host, unsigned short port, int rows, int columns, int playerId, int level): _game(columns, rows)
{
    Player * playerKi = 0;

    LOG << "Create GameHandler(host = " << host << ", port = " << port
    << ", rows = " << rows << ", columns = " << columns
    << ", playerId = " << playerId << ", level = " << level << ");" << std::endl;

    if(DataHandlingService::getInstance().start(host, port) < 0)
    {
        //cannot connect to the server
        // ToDo: Log-Tool
        LOG_ERROR << "Cannot connect to broker" << std::endl;
        exit(-1);
    }
    LOG << "Init vgr-client" << std::endl;

    switch (level)
    {
    case 0:
        playerKi = new SimulatePlayer(2);
        break;
    case 1:
        playerKi = new SimulatePlayer(4);
        break;
    case 2:
        playerKi = new SimulatePlayer(6);
        break;
    default:
        playerKi = new SimulatePlayer(1);
        break;
    }

    switch (playerId)
    {
    case 1:
        this->_game.addPlayer(playerKi);
        this->_game.addPlayer(new NetworkPlayer());
        LOG << "I am Player 1. " << std::endl;
        break;
    case 2:
        this->_game.addPlayer(new NetworkPlayer());
        this->_game.addPlayer(playerKi);
        LOG << "I am Player 2. " << std::endl;
        break;
    }
}

void GameHandler::run(void)
{
    DataHandlingService & service = DataHandlingService::getInstance();
    this->runRegisterClientAtBroker();

    while(true)
    {
        ServerNetworkMessage message = service.receiveMessage();
        switch (message.getType())
        {
        case NetworkMessageType::Request:
            this->runRequest();
            break;
        case NetworkMessageType::Move:
            this->runMove(message.getColumn(), message.getPlayerId());
            break;
        case NetworkMessageType::EndGame:
            return;
        case NetworkMessageType::Answer:
        default:
            LOG_ERROR << "error - invalid Messagetype: " << message.getType() << std::endl;
            return;
        }
    }
}

inline void GameHandler::runRequest(void)
{
    LOG << "RunRequest()" << std::endl;
    /*if (this->_game.getCurrentPlayer().getId() != this->_playerNumber + 1) {
        std::cout << "currentPlayer = " << this->_game.getCurrentPlayer().getId()
        << ", playerNumber = " << this->_playerNumber << std::endl;

        throw "Invalid Move Request. It is not my turn.";
    }*/

    int gameMove = this->_game.getCurrentPlayer().getMove(this->_game);
    ClientNetworkMessage message;
    message.setAnswerColumn(gameMove);
    //TODO do not use getCurrentPlayer
    DataHandlingService & service = DataHandlingService::getInstance();
    service.sendMessage(message);
}

inline void GameHandler::runMove(int column, int playerId)
{
    LOG << "RunMove(" << column << ", " << playerId << ")" << std::endl;
    //TODO check playerId
    this->_game.putStone(column);
    LOG << this->_game.currentMap << std::endl;
}

inline void GameHandler::runRegisterClientAtBroker(void)
{
    LOG << "Register to Broker with 42" << std::endl;
    ClientNetworkMessage message;
    message.setRegisterMessage();

    DataHandlingService & service = DataHandlingService::getInstance();
    service.sendMessage(message);
}

void GameHandler::runDebug(void)
{
    int gameMove;
    int winner;
    LOG << "Run vgr-client" << std::endl;
    LOG << "Compiled from " << __cplusplus << " at " __DATE__ << " - " << __TIME__ << std::endl;
    LOG << "Playing on Map[" << this->_game.currentMap.mapArray.size() << "][" << this->_game.currentMap.mapArray[0].size() << "]" << std::endl;

    this->_playerNumber = 1;

    while(this->_game.currentMap.isMovePossible())
    {
        // print current grid
        LOG << this->_game.currentMap;

        //ask player for move
        gameMove = this->_game.getCurrentPlayer().getMove(this->_game);

        //validate Move

        //get Rating
        LOG << "Rating = " << (Rating(this->_game, 1, 0)).rate(this->_game.currentMap) << std::endl;

        //execute Move
        this->_game.putStone(gameMove);
    }


    LOG << std::endl << "Game ended. ";
    winner = this->_game.currentMap.getWinner();
    if (winner < 0)
    {
        LOG << "It is a draw. ";
    }
    else
    {
        LOG << "Player #" << winner << " won. ";
    }
    LOG << "Final grid: " << std::endl << this->_game.currentMap << std::endl;
}
