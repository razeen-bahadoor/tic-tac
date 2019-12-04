#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#define PORT_NUM 51717


int main(int argc, char *argv[]){

	int sock_fd, newsock_fd,clilen,n;
	char move[2];
	struct sockaddr_in server_addr,client_addr;

	

	/*create a new socket*/
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock_fd ==0) {
		fprintf(stderr, "failed to create socket");
	}
	
	bzero((char *) &server_addr,sizeof(server_addr));

	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT_NUM);
	
	if (bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		fprintf(stderr,"error bidning");
		exit(1);
	}

	listen(sock_fd,5);

	clilen = sizeof(client_addr);
	
	newsock_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &clilen);

	if (newsock_fd < 0) {
		fprintf(stderr, "accept error");
	}

	bzero(move, sizeof(move));
	
	n = write(newsock_fd, "hello world", 11);
	if (n<0) {
		fprintf(stderr,"error writing");
		exit(1);
	}
	return EXIT_SUCCESS;


 /*read and write here*/	

	
}
