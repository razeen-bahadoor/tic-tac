/**
 * @file	game.h
 * @brief	drives the game
 * @author	Razeen Bahadoor 
 * @date 	2019-28-11
*/
#ifndef GAME_H
#define GAME_H

/**
* @brief initialise the game state
*
* @param[p1]
* @param[p2]
*/
void init_game(Player *p1,Player *p2);



/**
* @brief get the x and y coords from the player
*
* @param[x] pointer to integer var input will be propagated up
* @param[y] pointer to integer var 
*/
void get_move(int *x, int *y);


/**
* @brief checks is the move is valid
*
* @param[x] x coordinate
* @param[y] y coordinate 
*
* @return true/false
*/
Boolean is_valid_move(int x, int y);



/**
* @brief check the status of the game win/draw 
*
* @param[p] the current player 
*/
void game_status(Player p, int x, int y);

Boolean check_win(Player p, int x, int y);

/**
* @brief prints out the current board
*
* @param board[][] the board to print 
*/
void print_board(Player p);

#endif
