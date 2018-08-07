#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>

#define PORT 50000
#define BUF 100

int main(int argc ,char *argv[] ){
	int sock_fd;
	struct sockaddr_in to_s_addr;
	short port = 50000;
	size_t msg_len;
	ssize_t numRead;
	char buf[BUF];

	if(argc < 2 || strcmp(argv[1] , "--help") == 0){
		perror("input error\n");
		exit(1);
	}

	if( (sock_fd = socket(AF_INET , SOCK_DGRAM , 0)) == -1){
		perror("socket error\n");
		exit(1);
	}

	memset(&to_s_addr , 0 , sizeof(struct sockaddr_in));
	to_s_addr.sin_family = AF_INET;
	to_s_addr.sin_port = htons(port);
	if( inet_pton(AF_INET , "127.0.0.1" , &to_s_addr.sin_addr) <1 ){
		perror("inet_pton error\n");
		exit(1);
	}

	for(int i=1 ; i<argc ; i++){
		msg_len = strlen(argv[i]);
		if( sendto( sock_fd , argv[i] , msg_len , 0 , (struct sockaddr *) &to_s_addr , sizeof(struct sockaddr_in)) != msg_len){
			perror("sendto error\n");
			exit(1);
		}

		if( (numRead = recvfrom( sock_fd , buf , BUF , 0 , NULL , NULL)) == -1 ){
			perror("recvfrom error\n");
			exit(1);
		}
		else{
			printf("response : %d , %.*s\n" , i , numRead , buf );
		}
	}

	exit(EXIT_SUCCESS);
}