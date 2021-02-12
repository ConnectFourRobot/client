#include "../../include/game/GameSettings.hpp"

GameSettings::GameSettings(int sizeX, int sizeY):
    //initializer
    sizeX(sizeX),
    sizeY(sizeY),
    currentMap(sizeX, sizeY),
    currentPlayerId(1),
    players(std::vector<Player *>(0))
{
}

void GameSettings::addPlayer(Player * player)
{
    player->setId(1 + this->players.size());
    this->players.push_back(player);
}

Player & GameSettings::getPlayer(int8_t playerNumber)
{
    return *(this->players[playerNumber - 1]);
}

Player & GameSettings::getCurrentPlayer()
{
    return this->getPlayer(this->currentPlayerId);
}

void GameSettings::putStone(int column)
{
    this->currentMap.putStone(this->currentPlayerId, column);
    this->currentPlayerId++;
    if (this->currentPlayerId > static_cast<int>(this->players.size()))
    {
        this->currentPlayerId = 1;
    }
}
