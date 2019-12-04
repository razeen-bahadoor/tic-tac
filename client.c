#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#define PORT_NUM 51717
#define h_addr h_addr_list[0]


int main(int argc, char *argv[]) {

	int sock_fd, n;
	struct sockaddr_in server_addr;
	struct hostent *host_info;
	char buffer[256];
	if (argc < 2) {
		fprintf(stderr, "usage %s hostname", argv[0]);
		exit(1);
	}
	
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "error opening socket");
		exit(1); 
	}

	host_info = gethostbyname(argv[1]);
	
	if (host_info == NULL) {

		fprintf(stderr, "host not found");
		exit(1);
	}
	bzero((char *) &server_addr,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	bcopy((char *)host_info->h_addr, (char *) &server_addr.sin_addr.s_addr, host_info->h_length);

	server_addr.sin_port = htons(PORT_NUM);

	if (connect(sock_fd, (struct sockaddr *) &server_addr,sizeof(server_addr) )<0) {
		fprintf(stderr, "error connecting");
		exit(1);
	}
	
	bzero(buffer,256);
	n = read(sock_fd,buffer,255);
	if (n<0) {
		fprintf(stderr,"error reading from socket");
		exit(1);
	}
	
	printf("%s\n", buffer);
	return EXIT_SUCCESS;
	

}
