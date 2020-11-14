#include "../../include/game/Game.hpp"

Game::Game(int sizeX, int sizeY):
    //initializer
    sizeX(sizeX),
    sizeY(sizeY),
    currentMap(sizeX, sizeY),
    currentPlayerId(1),
    players(std::vector<Player *>(0))
{
}

void Game::addPlayer(Player * player)
{
    player->setId(1 + this->players.size());
    this->players.push_back(player);
}

Player & Game::getPlayer(int8_t playerNumber)
{
    return *(this->players[playerNumber - 1]);
}

Player & Game::getCurrentPlayer()
{
    return this->getPlayer(this->currentPlayerId);
}

void Game::putStone(int column)
{
    this->currentMap.putStone(this->currentPlayerId, column);
    this->currentPlayerId++;
    if (this->currentPlayerId > static_cast<int>(this->players.size()))
    {
        this->currentPlayerId = 1;
    }
}
