#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

#define BUF_SIZE 10
#define PORT 50002

int main(int argc , char *argv[]){
	struct sockaddr_in6 s_addr;
	int sfd;
	size_t msg_len;
	ssize_t numRead;
	char response[BUF_SIZE];



	if( (sfd = socket(AF_INET6 , SOCK_DGRAM , 0)) == -1){
		perror("socket error\n");
		exit(1);
	}

	memset(&s_addr , 0 , sizeof(struct sockaddr_in6));
	s_addr.sin6_family = AF_INET6;
	s_addr.sin6_port = htons(PORT);
	if( inet_pton(AF_INET6 , "::1" , &s_addr.sin6_addr) <1 ){
		perror("inet_pton error\n");
		exit(1);
	}
	for(int i=1 ; i<argc ; i++){

		msg_len = strlen(argv[i]);
		printf("msg_len : %d\n" , msg_len);
		if( sendto(sfd , argv[i] , msg_len , 0 , (struct sockaddr *)&s_addr , sizeof(struct sockaddr_in6)) != msg_len){
			perror("sendto error\n");
			exit(1);
		}

		memset(&response , 0 , strlen(response) );
		
		if( (numRead = recvfrom(sfd , response , BUF_SIZE , 0 , NULL , NULL)) ==-1 ){
			perror("recvfrom error\n");
			exit(1);
		}
		printf(" numRead : %d , response %d : %.*s\n" , numRead , i , (int)numRead , response);
	}
	exit(EXIT_SUCCESS);
}