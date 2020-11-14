#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cinttypes>
class Game;

class Player{
    protected:
        uint8_t id;

    public:
        Player() : id(1){};
        ~Player() {}
        inline void setId(int id) {this->id = id;}
        inline int getId() const {return this->id;}

        virtual int getMove(Game & game) = 0;
};
#endif
