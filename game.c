#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "boolean.h"
#include "player.h"
#include "ctype.h"
#include "game.h"

void init_player(Player *p, char player_sym) 
{
	
	printf("Player,please enter your name:");
	fgets(p->player_name, 255, stdin);
	p->player_name[strlen(p->player_name) - 1] = '\0';
	p->player_symbol = player_sym;
	printf("\n");

	
}

void get_move(int *x, int  *y) 
{

	char x_temp,y_temp;
	printf("row:");

	scanf("%c", &x_temp);
	while ((getchar()) != '\n'); /*flush stdin*/
	

	
	printf("\ncolumn:");
	scanf("%c", &y_temp);	
	printf("\n");

	/*loop until move is valid*/
	while((getchar()) != '\n');	 
	while (is_valid_move(x_temp-'0', y_temp-'0') == FALSE) {
		fprintf(stderr, "Error: invalid move,please try again\n");
	
		printf("row:");

		scanf("%c", &x_temp);
		while ((getchar()) != '\n');
	

	
		printf("\ncolumn:");
	
		scanf("%c", &y_temp);	
		printf("\n");
		while((getchar()) != '\n');	 
	}	
	*x = x_temp -'0';
	*y = y_temp - '0';
	
	
}

Boolean is_valid_move(int x, int y) 
{


	 if (x<0 || x>2) {
		return FALSE;
	} else if (y<0 ||  y>2) {
		return FALSE;
	} else if (is_empty(x, y) == FALSE) {
		return FALSE;
		
	} else {
		return TRUE;
	}
	

}


char* game_status(Player p, int x, int y)
{
	
	if (check_win(p, x, y) == TRUE) {
		return "WIN";
	} else if (is_full() == TRUE) {
		return "DRAW";
	} else {
		return "CONTINUE";	
	}

}

Boolean check_win(Player p, int x, int y){

	int row,col;
	
	/*check row */
	Boolean state;
	state = FALSE;
	for(col =0; col<3; col++) {
		if (get_piece(x, col) != p.player_symbol) {
			break;
		} else {
			if (col == 2) {
				state = TRUE;					
			} else {
				continue;
			}
		}
		
	}
	
	if (state == TRUE) {return TRUE;}
	
	/*check column*/
	for (row = 0; row<3; row++) {
		if (get_piece(row, y) != p.player_symbol) {
			break;
		} else {
			if (row == 2) {
				state = TRUE;
			} else {

				continue;
			}
			
		}
	}
	
	if (state == TRUE) {return TRUE;}
	
	if (x == y || x*y == 0) {
		col =0;
		/*check diagonal*/
		for (row =0; row < 3; row++) {
			if (get_piece(row, col) != p.player_symbol) {
				break;
			} else {
				if (row == 2) {
					state = TRUE; 
				} else {
					col++;
					continue;
				}
			}
	
		}
	
		if (state == TRUE) {return TRUE;}
		col =2;
		for (row =0; row<3; row++) {
		
			if (get_piece(row, col) != p.player_symbol) {
				break;
			} else {
				if (row == 2){
					state = TRUE;
				} else {
					col--;
					continue;
				}
			}	
		}
		if (state == TRUE) {return TRUE;}
	}		
	
	
	return FALSE;
	
}



void print_board(char name[])
 {
	int row,col;
	printf("Player 1:X Player 2:O\n");
	printf("Turn: %s\n", name);
	printf("\n");
	printf("  0 1 2\n");
	for(row =0; row<3; row++) {
		printf("%d ", row);
		for(col = 0; col < 3; col++) {
				
			if(get_piece(row, col) == 0) {
				printf(". ");
			} else {

				printf("%c ", get_piece(row, col));
			}
		}
		printf("\n");
	}
}
