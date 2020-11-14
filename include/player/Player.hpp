#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cinttypes>
class Game;

class Player
{
protected:
    /** playerId */
    uint8_t id;

public:
    /** constructor */
    Player() : id(1) {};

    /** destructor */
    ~Player() {}

    /** setter for playerId */
    inline void setId(int id)
    {
        this->id = id;
    }

    /** getter for playerId */
    inline int getId() const
    {
        return this->id;
    }

    /**
    * ask the bot for its turn
    *
    * @param Game & game
    * @return int column (0 - sizeX-1)
    */
    virtual int getMove(Game & game) = 0;
};
#endif
