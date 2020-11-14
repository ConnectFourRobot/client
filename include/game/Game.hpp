#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Grid.hpp"
#include "Player.hpp"
#include "PossibleMove.hpp"

class Game {
    public:
        const int sizeX;
        const int sizeY;
        Grid currentMap;
        std::vector<Player> players;

        Game(int sizeX, int sizeY, int numberOfPlayers);

       // Game() : sizeX(0), sizeY(0) {};

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

        /**
         * check if player has "numberOfStones" in a row
         *
         * @param numberOfStones Number of stones the player has to have in a row to return true
         * @param grid the corresponding grid
         * @param player
         * @return True if the player has numberOfStones in a row, false if not
        */
        bool checkLine(int numberOfStones, Grid& grid, Player player);
};
#endif
