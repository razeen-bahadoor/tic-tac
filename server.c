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

	
	int sock_fd,newsock_fd,val;
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t sock_size = sizeof(struct sockaddr_in);
	

	
	/*create socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == 0) {
		fprintf(stderr, "ERROR: failed to create socket\n");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT_NUM);
	
	/*bind the port to the socket*/

	if (bind(sock_fd, (struct sockaddr*)&serv_addr, 
				sizeof(serv_addr)) < 0 ) {

		fprintf(stderr, "ERROR: failed to bind\n");
		exit(1);
	}

	listen(sock_fd, 5);
	
	newsock_fd = accept(sock_fd, (struct sockaddr*)&clie_addr, 
				&sock_size);	
	
	
	if (newsock_fd < 0) {
		fprintf(stderr,"error accepting connection");
		exit(1);
	}

	



	Player p;
	char game_state[256];
	char opponent_name[256];
	int x_temp,y_temp;
	int32_t x,y;

	init_player(&p, 'X');
	
	/*send name to client*/
	write(newsock_fd, p.player_name, strlen(p.player_name));
	/*receive client name*/
	read(newsock_fd, opponent_name, 255);
		
	while (1) {
		print_board(p.player_name);
		get_move(&x_temp,&y_temp);
		place_piece(x_temp,y_temp,p.player_symbol);
		print_board(opponent_name);
		/*write move to client */
		x = htonl(x_temp);
		y = htonl(y_temp);
		send(newsock_fd, &x, sizeof(x), 0);
		send(newsock_fd, &y, sizeof(y), 0);
		
		/*write game state to client*/
		bzero(game_state, sizeof(game_state));
		strcpy(game_state, game_status(p,x_temp,y_temp));
		write(newsock_fd, game_state, strlen(game_state));
		

		
		
		/*check own game state*/
		if (strcmp(game_state, "WIN") == 0){
			printf("%s has won the game\n", p.player_name);
			exit(1);
		} else if (strcmp(game_state, "DRAW") == 0) {
			printf("%s and %s have drawn\n", p.player_name, opponent_name);
			exit(1);
		} else {
		
		}

		printf("waiting for move from %s ....\n", opponent_name);
		printf("\n");
		/*read move from client*/
		recv(newsock_fd, &x, sizeof(x), 0);
		x_temp = ntohl(x);
		recv(newsock_fd, &y, sizeof(y), 0);
		y_temp = ntohl(y);

		place_piece(x_temp,y_temp,'O');

		/*read game state from client*/
		bzero(game_state,sizeof(game_state));
		read(newsock_fd, game_state,255);

		if (strcmp(game_state, "WIN") == 0){
			print_board(opponent_name);
			printf("%s has won the game\n", opponent_name);
			exit(1);
		} else if (strcmp(game_state, "DRAW") == 0) {
			print_board(opponent_name);
			printf("%s and %s have drawn\n", p.player_name, opponent_name);
			exit(1);
		} else {
		
		}
				
	}
	
	return EXIT_SUCCESS;

	
}
