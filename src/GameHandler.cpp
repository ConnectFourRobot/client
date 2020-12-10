#include "../include/GameHandler.hpp"

GameHandler::GameHandler() {
    // ToDo: connect to broker
    std::cout << "Init vgr-client" << std::endl;
}

void GameHandler::run() {
    std::cout << "Run vgr-client" << std::endl;

    // Just for testing purposes!!!
    this->_playerNumber = 1;
    // init Game
    this->_game = Game(7, 6, 2);
    // print empty grid
    std::cout << this->_game.currentMap << std::endl;
    // throw stone
    this->_game.setStone(this->_game.getPlayer(this->_playerNumber), 3, this->_game.currentMap);
    // print new grid
    std::cout << this->_game.currentMap << std::endl;

    // throw opponent stone
    this->_game.setStone(this->_game.getPlayer(2), 4, this->_game.currentMap);
    // print new grid
    std::cout << this->_game.currentMap << std::endl;
}