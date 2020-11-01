#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Grid.hpp"
#include "Player.hpp"
#include "PossibleMove.hpp"

class Game {
    public: 
        int SizeX;
        int SizeY;
        Grid CurrentMap;
        std::vector<Player> Players;

        Game(int sizeX, int sizeY, int numberOfPlayers);

        Game() : SizeX(0), SizeY(0) {};

        /**
         * Put a stone in a column
         *
         * @param Player Owner of the stone
         * @param x Column
         * @param Grid The corresponding grid
        */
        void setStone(Player player, int x, Grid& grid);

        /**
         * Get all moves that are possible
         *
         * @param player The Player for wich this should be calculated 
         * @param grid Grid on wich this should be calculated 
         * @return possible moves
        */
        std::vector<PossibleMove> getPossibleMoves(Player player, Grid grid);

        /**
         * Get player with playernumber
         *
         * @param playerNumber Number of player that should be returned
         * @return player
        */
        Player getPlayer(int8_t playerNumber);
};
#endif