#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>

class Grid {
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
        */
        std::vector<std::vector<uint8_t>> MapArray;

        Grid(){};
        Grid(std::vector<std::vector<uint8_t>> mapArray) : MapArray(mapArray) {};

        /**
         * Get the value on a coordinate
         *
         * @param x X Coordinate of the stone
         * @param y Y Coordinate of the stone
         * @return value of the coordinates
        */
        inline uint8_t& getStone(int x, int y) {
            return MapArray[y][x];
        }

        /**
         * Prints the mapArray
        */
        friend std::ostream& operator << (std::ostream &out, const Grid &g){
            for(std::vector<uint8_t> iv : g.MapArray){
                for(uint8_t i : iv){
                    out << (int)i << " ";
                }
                out << std::endl;
            }
            return out;
        }
};
#endif