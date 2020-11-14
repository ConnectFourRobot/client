#include "../../include/game/Game.hpp"

Game::Game(int sizeX, int sizeY):
    //initializer
    currentMap(sizeX, sizeY),
    sizeX(sizeX),
    sizeY(sizeY),
    players(std::vector<Player *>(0)),
    currentPlayerId(1)
{
    // init players
    //std::vector<Player> players(0);
    //players.reserve(2);
}

void Game::addPlayer(Player * player)
{
    player->setId(1 + this->players.size());
    this->players.push_back(player);
}

/*
std::vector<PossibleMove> Game::getPossibleMoves(Player player, Grid grid){
    std::vector<PossibleMove> moves;
    moves.reserve(this->sizeX);
    for(int x = 0; x < this->sizeX; x++){
        if(grid.isColumnNotFull(x)){
            this->setStone(player, x, grid);
            moves.push_back(PossibleMove(x, grid));
        }
    }
    return moves;
}
*/
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
    if (this->currentPlayerId > this->players.size()) {
        this->currentPlayerId = 1;
    }
}
/*
bool Game::checkLine(int numberOfStones, Grid& grid, Player player) {
    int lineSize = 4;
    // verticalCheck
    for (int y = 0; y < this->sizeY-3 ; y++ ){
        for (int x = 0; x < this->sizeX; x++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x, y + s) != player.getId()) {
                   // check if field is free
                   if(grid.getStone(x, y + s) == 0 && emptyCounter < (lineSize-numberOfStones)) {
                       emptyCounter++;
                   } else {
                       brk = true;
                   }
               }

            }
            if(brk == false) {
                return true;
            }
        }
    }

    // horizontalCheck
    for (int x = 0; x < this->sizeX-3; x++ ){
        for (int y = 0; y < this->sizeY; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x + s, y) != player.getId()) {
                   // check if field is free
                   if(grid.getStone(x + s, y) == 0 && emptyCounter < (lineSize-numberOfStones)) {
                       emptyCounter++;
                   } else {
                       brk = true;
                   }
               }

            }
            if(!brk) {
                return true;
            }
        }
    }
    // ascendingDiagonalCheck
    for (int x=3; x < this->sizeX; x++){
        for (int y=0; y < this->sizeY-3; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x - s, y + s) != player.getId()) {
                   // check if field is free
                   if(grid.getStone(x - s, y + s) == 0 && emptyCounter < (lineSize-numberOfStones)) {
                       emptyCounter++;
                   } else {
                       brk = true;
                   }
               }

            }
            if(!brk) {
                return true;
            }
        }
    }
    // descendingDiagonalCheck
    for (int x=3; x < this->sizeX; x++){
        for (int y=3; y < this->sizeY; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x - s, y - s) != player.getId()) {
                   // check if field is free
                   if(grid.getStone(x - s, y - s) == 0 && emptyCounter < (lineSize-numberOfStones)) {
                       emptyCounter++;
                   } else {
                       brk = true;
                   }
               }

            }
            if(!brk) {
                return true;
            }
        }
    }
    return false;
}
*/
