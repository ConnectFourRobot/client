#ifndef RATING_COUNTER_HPP
#define RATING_COUNTER_HPP

#include "RatingScore.hpp"
#include "Rating.hpp"

class RatingCounter {
private:
    /**
    * neutral1 - block1 - neutral2 - block2 - neutral3
    */
    uint8_t stoneCounts[5];

    int countIndex;

    /** playerId of block1 and block2 */
    uint8_t playerId;

    /** score so far */
    intMoveScore score;

    //Rating & rating;

    inline void addingAfterNeutral(int stone);
    inline void addingAfterBlock(int stone);
    void toRating(void);

    int playerSelfId;

public:
    RatingCounter(int playerSelfId);
    intMoveScore getScoreAndReset(void);
    void resetAll();
    void add(int stone);
    void nextBlock(void);


};

#endif // RATING_COUNTER_HPP
