/**
 * @file	player.h
 * @brief	player profile for game
 * @author	Razeen Bahadoor 
 * @date 2019-28-11
*/

#ifndef PLAYER_H
#define PLAYER_H
typedef enum symbol {
	X,O
} Symbol;

typedef struct player {

	char player_name[256];
	Symbol player_symbol;

} Player;

#endif
