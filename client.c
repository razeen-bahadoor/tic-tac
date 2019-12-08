#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include "player.h"
#include "board.h"
#include "game.h"
#define PORT_NUM 51717



int main(int argc, char *argv[]) {
	
	
	int sock_fd,val;
	struct sockaddr_in clie_addr;
	

	if (argc < 2 ) {
		printf("ERROR: usage /.%s <server ip>", argv[0]);
		exit(1);
	}
	
	/*create the socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr,"socket creation failed");
		exit(1);
	}
	
	clie_addr.sin_family = AF_INET;
	clie_addr.sin_port = htons(PORT_NUM);

	if (inet_pton(AF_INET, argv[1], &clie_addr.sin_addr) <= 0) {
		fprintf(stderr, "invalid ip address");
		exit(1);
	}

	/*connect to the server*/
		
	if (connect(sock_fd, (struct sockaddr *)&clie_addr, sizeof(clie_addr)) <0) {

		fprintf(stderr, "connection to server failed");
		exit(1);
	}

	


	Player p;
	char game_state[256];

	int x_temp,y_temp;
	int32_t x,y;
	init_player(&p, 'O');
	/*send name here*/
	/*read name here*/
	while (1){

		
		print_board("raz");
		/*read move from server here*/
		
		recv(sock_fd,&x, sizeof(x),0 );

		x_temp = ntohl(x);
		recv(sock_fd,&y,sizeof(y),0);

		y_temp = ntohl(y);
		
		place_piece(x_temp,y_temp,'X');

		bzero(game_state,sizeof(game_state));
		read(sock_fd,game_state,255);
		
		if (strcmp(game_state, "WIN") == 0) {
					print_board("raz");
			printf("player has won");
			exit(1);
		} else if (strcmp(game_state, "DRAW") ==0) {
					print_board("raz");
			printf("players have drawn");
			exit(1);
		} else {
		
		}

		print_board("zen");
		get_move(&x_temp,&y_temp);	
		place_piece(x_temp,y_temp,p.player_symbol);

		/*write move to server here*/
		x = htonl(x_temp);
		y = htonl(y_temp);

		send(sock_fd,&x,sizeof(x), 0);
		send(sock_fd,&y,sizeof(y), 0);

		bzero(game_state,sizeof(game_state));
		strcpy(game_state, game_status(p,x_temp,y_temp));
		write(sock_fd,game_state,strlen(game_state));
		if (strcmp(game_state, "WIN") == 0) {
			printf("player has won");
			exit(1);
		} else if (strcmp(game_state, "DRAW") ==0) {
			printf("players have drawn");
			exit(1);
		} else {
		
		}

	}
	return EXIT_SUCCESS;
	

}
