#ifndef RATING_SCORE_HPP
#define RATING_SCORE_HPP

#include <cinttypes>

typedef int32_t intMoveScore;
#define RATING_VICTORY 30000
// get the playerId of the player who has not the given playerId (toggle 1 <=> 2)
#define otherPlayer(pid) (3 - ( pid ))

#endif // RATING_SCORE_HPP
