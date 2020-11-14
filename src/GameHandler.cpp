#include "../include/GameHandler.hpp"

GameHandler::GameHandler(std::string host, unsigned short port): _game(7, 6, 2) {
    // ToDo: connect to broker
    if(DataHandlingService::getInstance().start(host, port) < 0){
        //cant connect to the server
        // ToDo: Log-Tool
        std::cout << "Can not connect to broker" << std::endl;
        exit(0);
    }
    std::cout << "Init vgr-client" << std::endl;
}

void GameHandler::run() {
    std::cout << "Run vgr-client" << std::endl;

    // Just for testing purposes!!!
    this->_playerNumber = 1;
    // init Game
    //this->_game = Game(7, 6, 2);
    // print empty grid
    std::cout << this->_game.currentMap << std::endl;
    // throw stone
    this->_game.currentMap.putStone(this->_playerNumber, 3);
    // print new grid
    std::cout << this->_game.currentMap << std::endl;

    // throw opponent stone
    this->_game.currentMap.putStone(2, 4);
    // print new grid
    std::cout << this->_game.currentMap << std::endl;

    // throw stone
    this->_game.currentMap.putStone(this->_playerNumber, 3);
    // print new grid
    std::cout << this->_game.currentMap << std::endl;

    //find all moves
    auto moves = PossibleMove::calcPossibleMoves(this->_game.currentMap, this->_game, 2);
    this->_game.currentMap = moves->next->afterGrid;

    // print new grid
    std::cout << this->_game.currentMap << std::endl;

    std::cout << "Map[" << this->_game.currentMap.mapArray.size() << "][" << this->_game.currentMap.mapArray[0].size() << "]" << std::endl;

}
