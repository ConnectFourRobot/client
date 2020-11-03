#include "../../include/game/Game.hpp"

Game::Game(int sizeX, int sizeY, int numberOfPlayers) {
    // init grid
    std::vector<std::vector<uint8_t>> mapArray(sizeY, std::vector<uint8_t>(sizeX, 0));
    Grid grid(mapArray);
    
    // init players
    std::vector<Player> players;
    for(uint8_t i = 1; i <= numberOfPlayers; i++){
        Player p(i);
        players.push_back(p);
    }

    this->SizeX = sizeX;
    this->SizeY = sizeY;
    this->CurrentMap = grid;
    this->Players = players;
}

void Game::setStone(Player player, int column, Grid& grid){
    int row = 0;
    for(int i = 0; i < this->SizeY; i++){
        if(grid.getStone(column, row) == 0){
            row++;
        }else{
            break;
        }
    }
    grid.getStone(column, row - 1) = player.Id;
}

std::vector<PossibleMove> Game::getPossibleMoves(Player player, Grid grid){
    std::vector<PossibleMove> moves;
    for(int x = 0; x < this->SizeX; x++){
        if(grid.getStone(x, 0) == 0){
            this->setStone(player, x, grid);
            moves.push_back(PossibleMove(x, grid));
        }
    }
    return moves;
}

Player Game::getPlayer(int8_t playerNumber){
    for (Player player : this->Players) {
        if(player.Id == playerNumber) {
            return player;
        }
    }
    // fallback
    return Player();
}

bool Game::checkLine(int numberOfStones, Grid& grid, Player player) {
    int lineSize = 4;
    // verticalCheck 
    for (int y = 0; y < this->SizeY-3 ; y++ ){
        for (int x = 0; x < this->SizeX; x++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x, y + s) != player.Id) {
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
    for (int x = 0; x < this->SizeX-3; x++ ){
        for (int y = 0; y < this->SizeY; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x + s, y) != player.Id) {
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
    for (int x=3; x < this->SizeX; x++){
        for (int y=0; y < this->SizeY-3; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x - s, y + s) != player.Id) {
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
    for (int x=3; x < this->SizeX; x++){
        for (int y=3; y < this->SizeY; y++){
            bool brk = false;
            int emptyCounter = 0;
            for(int s = 0; s < lineSize && !brk; s++) {
               if(grid.getStone(x - s, y - s) != player.Id) {
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