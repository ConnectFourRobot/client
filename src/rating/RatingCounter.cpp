#include "../../include/rating/RatingCounter.hpp"
#include "../../include/game/Grid.hpp"

#define addingChangedPlayer {this->stoneCounts[1] = 1; this->stoneCounts[2] = 0; this->stoneCounts[3] = 0; this->stoneCounts[4] = 0; this->playerId = stone;}
#define maxIndexMacro(arr,i1,i2) (((arr[i2]) > (arr[i1])) ? (i2) : (i1))
#define hasOneMacro(a) (((a) > 0) ? 1 : 0)

RatingCounter::RatingCounter(const int playerSelfId): playerSelfId(playerSelfId) {
    this->resetAll();
}

inline void RatingCounter::addingAfterNeutral(int stone) {
    if (stone == Grid::EMPTY_FIELD) {
        //neutral block enlarge
        this->stoneCounts[this->countIndex]++;
    } else if (stone == this->playerId) {
        //is there another block?
        if (this->countIndex < 4) {
            this->countIndex++;
            this->stoneCounts[this->countIndex] = 1;
        } else {
            //special case: counting model full
            this->toRating();
            //remove the first neutral+block
            this->stoneCounts[0] = this->stoneCounts[2];
            this->stoneCounts[1] = this->stoneCounts[3];
            this->stoneCounts[2] = this->stoneCounts[4];
            this->stoneCounts[3] = 1;
            this->stoneCounts[4] = 0;
            this->countIndex = 3;
        }
    } else {
        //end of counting area
        this->toRating();
        this->stoneCounts[0] = this->stoneCounts[this->countIndex];
        addingChangedPlayer;
        this->countIndex = 1;
    }
}

inline void RatingCounter::addingAfterBlock(int stone) {
    if (stone == Grid::EMPTY_FIELD) {
        //switch to neutral block
        this->countIndex++;
        this->stoneCounts[this->countIndex] = 1;
    } else if (stone == this->playerId) {
        this->stoneCounts[this->countIndex]++;
    } else {
        this->toRating();
        this->stoneCounts[0] = 0;
        addingChangedPlayer;
        this->countIndex = 1;
    }
}

void RatingCounter::add(int stone) {
    if (this->countIndex % 2) {
        //e.g. countIndex = 1
        this->addingAfterBlock(stone);
    } else {
        //e.g. countIndex = 0
        this->addingAfterNeutral(stone);
    }
}

void RatingCounter::toRating(void) {
    int sumStones = this->stoneCounts[1] + this->stoneCounts[3];
    int maxIndex = maxIndexMacro(this->stoneCounts, 1, 3);
    int maxStones = this->stoneCounts[maxIndex];
    int sumFrees = this->stoneCounts[0] + this->stoneCounts[2] + this->stoneCounts[4];
    int openEnds = 0; //hasOneMacro(this->stoneCounts[0]);
    int addScore = 0;

    if (sumStones + sumFrees < 4 || sumStones == 0) {
        //no score if you cannot reach 4 stones
        return;
    }

    if (maxStones >= 3) {
        //block of three coherent stones
        openEnds = hasOneMacro(this->stoneCounts[maxIndex - 1]) + hasOneMacro(this->stoneCounts[maxIndex + 1]);
        if (openEnds > 1) {
            //both open end
            //example: 0 1 1 1 0 .
            addScore = 1000;
        } else {
            //single open end
            //example: 2 1 1 1 0 .
            addScore = 500;
        }
    } else if (maxStones >= 2 && sumStones >= 3 && this->stoneCounts[2] == 1) {
        //block of two coherent stones and another stone
        openEnds = hasOneMacro(this->stoneCounts[maxIndex - 1]) + hasOneMacro(this->stoneCounts[maxIndex + 1]);
        if (openEnds > 1) {
            //example: 0 1 1 0 1 .
            addScore = 150;
        } else {
            //example: 2 1 1 0 1 .
            addScore = 100;
        }
    } else if (maxStones >= 2) {
        //block of two coherent stones, but no other stone
        if ((this->stoneCounts[0] > 0) && (this->stoneCounts[2] > 0)) {
            //open to both sides
            //example: 0 1 1 0 . .
            addScore = 50;
        } else {
            //only one side open
            //example: 2 1 1 0 0 .
            addScore = 10;
        }
    } else if (sumStones >= 2) {
        //two single stones
        //example: . 1 0 0 1 .
        addScore = 3;
    } else {
        //one single stone
        //example: 0 1 0 0 . .
        addScore = 1;
    }

    if (this->playerId == this->playerSelfId) {
        this->score += addScore;
    } else {
        this->score -= addScore;
    }
}

void RatingCounter::resetAll(void) {
    for (int i = 0; i < 5; i++) {
        this->stoneCounts[i] = 0;
    }
    this->countIndex = 0;
    this->score = 0;
}

intMoveScore RatingCounter::getScoreAndReset(void) {
    intMoveScore result = 0;
    this->toRating();
    result = this->score;
    this->resetAll();
    return result;
}

void RatingCounter::nextBlock(void) {
    this->toRating();
    for (int i = 0; i < 5; i++) {
        this->stoneCounts[i] = 0;
    }
    this->countIndex = 0;
}
