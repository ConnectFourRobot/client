#ifndef GAME_STATE_ENUM_H
#define GAME_STATE_ENUM_H

/** an error occurred, so the game cannot be played */
#define GAMESTATE_ERROR_BIT 0x80

/** the game is still running */
#define GAMESTATE_RUNNING_BIT 0x40

/** the game is terminated and there is a winner */
#define GAMESTATE_WIN_BIT 0x20

/** location of the bits, where a winner is stored if win-bit is set */
#define GAMESTATE_PLAYERID_MASK 0x07 //bits 0x01, 0x02 and 0x04 are reserved for playerId

#endif //!GAME_STATE_ENUM_H
