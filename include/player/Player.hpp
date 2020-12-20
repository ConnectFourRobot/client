#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cinttypes>
class GameSettings;

/** abstract class Player participating the game*/
class Player
{
protected:
    /** playerId. begins with 1. */
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

    /** getter for playerId. Begins with 1. */
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
    virtual int getMove(GameSettings & game) = 0;
};
#endif
