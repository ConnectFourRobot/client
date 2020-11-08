#include "../../include/game/Game.hpp"

Game::Game(int sizeX, int sizeY, int numberOfPlayers) {
    // init grid
    Grid grid(sizeX, sizeY);
    
    // init players
    std::vector<Player> players;
    for(uint8_t i = 1; i <= numberOfPlayers; i++){
        Player p(i);
        players.push_back(p);
    }

    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->currentMap = grid;
    this->players = players;
}

void Game::setStone(Player player, int column, Grid& grid){
    int row = 0;
    for(int i = 0; i < this->sizeY; i++){
        if(grid.getStone(column, row) == Grid::emptyField){
            row++;
        }else{
            break;
        }
    }
    grid.getStone(column, row - 1) = player.id;
}

std::vector<PossibleMove> Game::getPossibleMoves(Player player, Grid grid){
    std::vector<PossibleMove> moves;
    for(int x = 0; x < this->sizeX; x++){
        if(grid.getStone(x, 0) == Grid::emptyField){
            this->setStone(player, x, grid);
            moves.push_back(PossibleMove(x, grid));
        }
    }
    return moves;
}

Player Game::getPlayer(int8_t playerNumber){
    for (Player player : this->players) {
        if(player.id == playerNumber) {
            return player;
        }
    }
    // fallback
    return Player();
}

bool Game::checkLine(int numberOfStones, Grid& grid, Player player) {
    int lineSize = 4;
    // verticalCheck 
    for (int y = 0; y < this->sizeY-3 ; y++ ){
        for (int x = 0; x < this->sizeX; x++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x, y + s) != player.id) {
                   // check if field is free
                   if(grid.getStone(x, y + s) == Grid::emptyField && emptyCounter < (lineSize-numberOfStones)) {
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
               if(grid.getStone(x + s, y) != player.id) {
                   // check if field is free
                   if(grid.getStone(x + s, y) == Grid::emptyField && emptyCounter < (lineSize-numberOfStones)) {
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
               if(grid.getStone(x - s, y + s) != player.id) {
                   // check if field is free
                   if(grid.getStone(x - s, y + s) == Grid::emptyField && emptyCounter < (lineSize-numberOfStones)) {
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
               if(grid.getStone(x - s, y - s) != player.id) {
                   // check if field is free
                   if(grid.getStone(x - s, y - s) == Grid::emptyField && emptyCounter < (lineSize-numberOfStones)) {
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