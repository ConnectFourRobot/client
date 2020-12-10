#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player{
    private:

    public:
        uint8_t id;

        Player(uint8_t id) :id(id){};
        Player() : id(1){};
};
#endif