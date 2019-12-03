/**
 * @file	board.h
 * @brief	board for game
 * @author	Razeen Bahadoor 
 * @date 2019-28-11
*/
#include "boolean.h"

#ifndef BOARD_H
#define BOARD_H


/**
* @brief initialises the game board
*/
void init_board(void);



/**
* @brief places the players piece at position (x,y)
*
* @param[x] x coordinate
* @param[y] y coordinate
* @param[piece] players piece 
*
* @return true/false
*/
void place_piece(int x,int y,char piece);



/**
* @brief checks if the cell at (x,y) is empty
*
* @param[x] x coordinate
* @param[y] y coordinate
*
* @return return true/false
*/
Boolean is_empty(int x, int y);



/**
* @brief checks whether the board is full
*
* @return 
*/
Boolean is_full(void);
/**
* @brief returns the player piece at position (x,y)
*
* @param[x] x coordinate
* @param[y] y coordinate
*
* @return the piece
*/
char get_piece(int x,int y);

#endif
