#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "board.h"



char game_board[3][3];


void  place_piece(int x,int y, char piece)
{
	game_board[x][y] = piece;
}

Boolean is_empty(int x, int y) 
{
	
	if (game_board[x][y] == 0) {return TRUE;}
	else {return FALSE;}
}

Boolean is_full(void)
{
	int row,col;
	for (row = 0; row<3; row++) {
		for (col =0; col<3; col++) {
			if (is_empty(row, col) == TRUE) {
				return FALSE;	
			}
		}
	}
	return TRUE;

}
 
char get_piece(int x, int y)
{
	return game_board[x][y];
}


