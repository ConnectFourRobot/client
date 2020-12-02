#include "../include/GameHandler.hpp"
#include "../include/player/DebugPlayer.hpp"
#include "../include/player/RandomMovePlayer.hpp"
#include "../include/player/SimulatePlayer.hpp"
#include "../include/player/NetworkPlayer.hpp"

//TODO delete these tests
#include "../include/rating/Rating.hpp"

GameHandler::GameHandler(std::string host, unsigned short port, int rows, int columns, int playerId, int level): _game(columns, rows)
{
    Player * playerKi = 0;
    // ToDo: connect to broker
    if(DataHandlingService::getInstance().start(host, port) < 0)
    {
        //cannot connect to the server
        // ToDo: Log-Tool
        std::cout << "Cannot connect to broker" << std::endl;
        exit(-1);
    }
    std::cout << "Init vgr-client" << std::endl;

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
        break;
    case 2:
        this->_game.addPlayer(new NetworkPlayer());
        this->_game.addPlayer(playerKi);
        break;

    }
}

void GameHandler::run(void)
{
    DataHandlingService & service = DataHandlingService::getInstance();

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
            std::cout << "error - invalid Messagetype: " << message.getType() << std::endl;
            //error
            break;
        }
    }
}

void GameHandler::runRequest(void)
{
    std::cout << "RunRequest()" << std::endl;
    int gameMove = this->_game.getCurrentPlayer().getMove(this->_game);
    //TODO do not use getCurrentPlayer
    DataHandlingService & service = DataHandlingService::getInstance();
    service.sendMessage(ClientNetworkMessage(gameMove));
}

void GameHandler::runMove(int column, int playerId)
{
    std::cout << "RunMove(" << column << ", " << playerId << ")" << std::endl;
    //TODO check playerId
    this->_game.putStone(column);
}

void GameHandler::runDebug(void)
{
    int gameMove;
    int winner;
    std::cout << "Run vgr-client" << std::endl;
    std::cout << "Compiled from " << __cplusplus << " at " __DATE__ << " - " << __TIME__ << std::endl;
    std::cout << "Playing on Map[" << this->_game.currentMap.mapArray.size() << "][" << this->_game.currentMap.mapArray[0].size() << "]" << std::endl;

    // Just for testing purposes!!!
    this->_game.addPlayer(new SimulatePlayer(7));
    this->_game.addPlayer(new SimulatePlayer(7));

    this->_playerNumber = 1;

    while(this->_game.currentMap.isMovePossible())
    {
        // print current grid
        std::cout << this->_game.currentMap;

        //ask player for move
        gameMove = this->_game.getCurrentPlayer().getMove(this->_game);

        //validate Move

        //get Rating
        std::cout << "Rating = " << (Rating(this->_game, 1, 0)).rate(this->_game.currentMap) << std::endl;

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
    char cc;
    std::cout << "Enter zum Beenden: ";
    std::cin >> cc;
}
