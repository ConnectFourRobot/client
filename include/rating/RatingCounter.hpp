#ifndef RATING_COUNTER_HPP
#define RATING_COUNTER_HPP

#include "RatingScore.hpp"
#include "Rating.hpp"

/** count score for rating a grid */
class RatingCounter {
private:
    /**
     * count of consecutive identical stones (only one party and neutrals)
     * neutral1 - block1 - neutral2 - block2 - neutral3
     * example: 1 1 1 0 0 1 1 ==> [0, 3, 2, 2, 0]
     * example: 1 0 0 0 2 2 0 ==> [0, 1, 3, 0, 0] for 1 and [3, 2, 1, 0, 0] for 2
     */
    uint8_t stoneCounts[5];

    /** the index of stoneCount, which is active */
    int countIndex;

    /** playerId of block1 and block2 */
    uint8_t playerId;

    /** score so far */
    intMoveScore score;

    /** evaluate given next stone. The stone before was neutral(0) */
    inline void addingAfterNeutral(int stone);

    /** evaluate given next stone. The stone before was occupied (1 or 2) */
    inline void addingAfterBlock(int stone);

    /** evaluate the stoneCounts array and add its score to this->score */
    void toRating(void);

    /** the playerId who gets positive score for its stones */
    const int playerSelfId;

public:
    /** constructor */
    RatingCounter(const int playerSelfId);

    /** reset the counter and give score
     * @return intMoveScore the score so far (will be resetted as well) */
    intMoveScore getScoreAndReset(void);

    /** reset the counter */
    void resetAll();

    /** evaluate given next stone
     * @param int stone the stone's playerId or neutral (0, 1 or 2) which should be evaluated */
    void add(int stone);

    /** a consecutive block of stones ended
     * example: end of line, next line will follow */
    void nextBlock(void);
};

#endif // RATING_COUNTER_HPP
