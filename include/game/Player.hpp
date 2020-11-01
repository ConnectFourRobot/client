#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player{
    private:

    public:
        uint8_t Id;

        Player(uint8_t id) : Id(id){};
        Player() : Id(1){};
};
#endif