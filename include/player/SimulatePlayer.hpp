#ifndef PLAYER_SIMULATEPLAYER_HPP
#define PLAYER_SIMULATEPLAYER_HPP

#include "../../include/game/PossibleMove.hpp"
#include "Player.hpp"

/** the default KI-Player thinking about a best move */
class SimulatePlayer : public Player
{
protected:
    /** how deep the bot should search for the best move */
    int depth;

    /** random factor also allows less good moves. It is the maximum score difference between the best move and the second best move.
     * randomFactor = 0: always choose best move */
    int randomFactor;

    /** search P2 move in vector */
    PossibleMove * getSecondBestMove(std::vector<PossibleMove> & moves, intMoveScore minimumRating);

public:
    /** constructor */
    SimulatePlayer(int depth = 2, int randomFactor = 3);

    /** @inheritdoc */
     virtual int getMove(GameSettings & game);

     /** default setter */
     inline void setDepth(int depth) {this->depth = depth;}
};

#endif //PLAYER_SIMULATEPLAYER_HPP
