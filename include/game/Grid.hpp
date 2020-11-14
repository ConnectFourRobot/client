#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include "GameState.hpp"

class Grid
{
public:
    /**
     * Array of stones
     * 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0
     * 0 1 1 1 1 2 0
     * 0 2 2 1 2 2 1
     *
     * inner vector: lines
     * outer vector: columns
     * mapArray[line][column] = stone-owner
    */
    std::vector<std::vector<uint8_t>> mapArray;

public:
    static const uint8_t emptyField = 0;

    /**
    * @see GameState.hpp
    */
    uint8_t stateOfGame;

public:
    /**
    * constructor
    */
    Grid(int sizeX, int sizeY);

    /**
    * copy constructor
    */
    Grid(const Grid&);

    /**
     * Get the value on a coordinate
     *
     * @param int x X Coordinate of the stone
     * @param int y Y Coordinate of the stone
     * @return uint8_t& value of the coordinates
    */
    inline uint8_t& getStone(int x, int y)
    {
        return this->mapArray[y][x];
    }

    /**
     * Get the value on a coordinate, if it is inbound
     * Otherwise (out of bounds) the value 255 will be returned
     *
     * @param int x X Coordinate of the stone
     * @param int y Y Coordinate of the stone
     * @return uint8_t value of the coordinates
    */
    inline uint8_t getStoneSafe(int x, int y);

    /**
     * is there still a place for another stone in the column
     * @param int x column (0 - sizeX-1)
     * @return bool false = column is full, true = column has free space
    */
    bool isColumnNotFull(int x);

    /**
    * @return bool true if there is an insertable stone
    */
    inline bool isPlayable(void)
    {
        return (this->stateOfGame & GAMESTATE_RUNNING_BIT) && !(this->stateOfGame & GAMESTATE_ERROR_BIT);
    }

    int getWinner(void);

    /**
    * Put a stone in a column
    *
    * @param int playerId Owner of the stone
    * @param column Column in wich the stone gets thrown
    * @return bool has a stone been inserted
    */
    bool putStone(int playerId, int column);

private:
    /**
     * search the row, into which a new stone would fall if inserted into the given column
     *
     * @param int x column whose stones should be counted
     * @return int index of free stone or -1 if full
    */
    int freeRow(int x);

    /**
     * check, if the inserted stone caused an end of the game
     *
     * @param int column where a stone has been inserted
     * @param int row where a stone has been inserted
     * @param int playerId whose stone has been inserted
     * @return void (The stateOfGame-Attribute could be updated)
    */
    inline void evaluateStone(int column, int row, int playerId);

public:
    /**
     * Prints the mapArray
    */
    friend std::ostream& operator << (std::ostream &out, const Grid &g);
};
#endif
