#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "board.h"
#include "game.h"
#define PORT_NUM 51717



int main(int argc, char *argv[]) 
{
	
	
	int sock_fd,val;
	struct sockaddr_in clie_addr;
	

	if (argc < 2 ) {
		printf("ERROR: usage /.%s <server ip>", argv[0]);
		exit(1);
	}
	
	/*create the socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr,"Error: failed to create socket\n");
		exit(1);
	}
	
	clie_addr.sin_family = AF_INET;
	clie_addr.sin_port = htons(PORT_NUM);

	if (inet_pton(AF_INET, argv[1], &clie_addr.sin_addr) <= 0) {
		fprintf(stderr, "Error: invalid ip address\n");
		exit(1);
	}

	/*connect to the server*/
	if (connect(sock_fd, (struct sockaddr *)&clie_addr, sizeof(clie_addr)) <0) {

		fprintf(stderr, "Error: failed to connect to the server");
		exit(1);
	}

	


	Player p;
	char game_state[256];
	char opponent_name[256];
	int x_temp,y_temp;
	int32_t x,y;
	init_player(&p, 'O');


	/*read name from server*/
	read(sock_fd, opponent_name, 255);
	/*write name to server*/
	write(sock_fd, p.player_name, strlen(p.player_name));

	while (1) {

		
		printf("waiting for move from %s ....\n", opponent_name);
		printf("\n");

		/*read move from server*/
		recv(sock_fd, &x, sizeof(x), 0);
		x_temp = ntohl(x);
		recv(sock_fd, &y, sizeof(y),0);
		y_temp = ntohl(y);
		
		place_piece(x_temp, y_temp, 'X');
		print_board(p.player_name);
	
		/*read game state from server*/
		bzero(game_state, sizeof(game_state));
		read(sock_fd, game_state,255);
		
		if (strcmp(game_state, "WIN") == 0) {
						printf("%s has won the game\n", opponent_name);
			exit(1);
		} else if (strcmp(game_state, "DRAW") == 0){
	printf("%s and %s have drawn\n", p.player_name, opponent_name);
			exit(1);
		} else {
		
		}

	
		get_move(&x_temp, &y_temp);	
		place_piece(x_temp, y_temp, p.player_symbol);
		print_board(opponent_name);
	
		/*write move to server*/
		x = htonl(x_temp);
		y = htonl(y_temp);
		send(sock_fd, &x, sizeof(x), 0);
		send(sock_fd, &y, sizeof(y), 0);
		/*write game state to server*/
		bzero(game_state, sizeof(game_state));
		strcpy(game_state, game_status(p, x_temp, y_temp));
		write(sock_fd, game_state, strlen(game_state));
	
		if (strcmp(game_state, "WIN") == 0) {
			printf("%s has won the game\n", p.player_name);
			exit(1);
		} else if (strcmp(game_state, "DRAW") ==0) {
					printf("%s and %s have drawn\n", p.player_name, opponent_name);
			exit(1);
		} else {
		
		}

	}
	return EXIT_SUCCESS;
	

}
