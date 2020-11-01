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

void Game::setStone(Player player, int x, Grid& grid){
    int y = 0;
    for(int i = 0; i < this->SizeY; i++){
        if(grid.getStone(x, y) == 0){
            y++;
        }else{
            break;
        }
    }
    grid.getStone(x, y-1) = player.Id;
}

std::vector<PossibleMove> Game::getPossibleMoves(Player player, Grid grid){
    std::vector<PossibleMove> moves;
    for(int x = 0; x < this->SizeX; x++){
        if(grid.getStone(x, 0) == 0){
            Grid cgrid(grid);
            this->setStone(player, x, cgrid);
            moves.push_back(PossibleMove(x, cgrid));
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