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


int main(int argc, char *argv[]){

	
	int sock_fd,newsock_fd,val;
	struct sockaddr_in serv_addr,clie_addr;
	socklen_t sock_size = sizeof(struct sockaddr_in);
	

	
	/*vreate socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if (sock_fd == 0) {
		fprintf(stderr,"socket creation failed");
		exit(1);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT_NUM);
	
	/*bind the port to the socket*/

	if (bind(sock_fd, (struct sockaddr*)&serv_addr, 
				sizeof(serv_addr)) < 0 ) {

		fprintf(stderr,"binding failed");
		exit(1);
	}

	listen(sock_fd,5);
	
	newsock_fd = accept(sock_fd, (struct sockaddr*)&clie_addr, 
				&sock_size);	
	
	
	if (newsock_fd < 0) {
		fprintf(stderr,"error accepting connection");
		exit(1);
	}

	
/*************************************************************START THE GAME*/

	/*make move on own board 
	  send move to client 
	  read move from client 
	   make move on own board */
	Player p;
	
	char game_state[256];
	int x_temp,y_temp;
	int32_t x,y;

	init_player(&p, 'X');
	/*read opponent name here*/
	/*send name here*/
	
	while (1){
		print_board("raz");
		get_move(&x_temp,&y_temp);/*get server move*/
	
		
		place_piece(x_temp,y_temp,p.player_symbol);


		

		/*write move to client here*/
		x = htonl(x_temp);
		y = htonl(y_temp);

		send(newsock_fd, &x,sizeof(x),0);

		send(newsock_fd, &y, sizeof(y),0);

		bzero(game_state,sizeof(game_state));
		strcpy(game_state,game_status(p,x_temp,y_temp));
		write(newsock_fd,game_state,strlen(game_state));
				print_board("zen");
		/*read move from client here*/
	
		if (strcmp(game_state,"WIN") == 0){
			printf("player has won");
			exit(1);
		} else if (strcmp(game_state,"DRAW") == 0) {
			printf("players have drawn");
			exit(1);
		} else {
		
		}
		recv(newsock_fd, &x, sizeof(x),0);
		x_temp = ntohl(x);
		recv(newsock_fd, &y, sizeof(y),0);
		y_temp = ntohl(y);

		place_piece(x_temp,y_temp,'O');

		bzero(game_state,sizeof(game_state));

		read(newsock_fd, game_state,255);

		if (strcmp(game_state,"WIN") == 0){
					print_board("raz");
			printf("player has won");
			exit(1);
		} else if (strcmp(game_state,"DRAW") == 0) {
					print_board("raz");
			printf("players have drawn");
			exit(1);
		} else {
		
		}
				
	}
	
	return EXIT_SUCCESS;


 /*read and write here*/	

	
}
