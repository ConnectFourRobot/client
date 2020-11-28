#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include <vector>

#include "Grid.hpp"
#include "../player/Player.hpp"
#include "PossibleMove.hpp"

/** The GameSettings, which do not change during a game is played. */
class GameSettings
{
public:
    const int sizeX;
    const int sizeY;
    Grid currentMap;
    int currentPlayerId;
    std::vector<Player *> players;

    /**
     * constructor
    */
    GameSettings(int sizeX, int sizeY);

    /**
     * Add given player to game
    */
    void addPlayer(Player * player);

    /**
     * Get player with playernumber
     *
     * @param playerNumber Number of player that should be returned
     * @return player
    */
    Player & getPlayer(int8_t playerNumber);

    /**
     * Get the player whose turn it is
     *
     * @return player
    */
    Player & getCurrentPlayer();

    /**
     * The player whose turn it is throw a stone into given column
     *
     * @param int column
    */
    void putStone(int column);
};
#endif //GAME_SETTINGS_HPP
