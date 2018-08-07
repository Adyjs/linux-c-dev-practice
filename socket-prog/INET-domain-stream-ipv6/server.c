#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "lib/tlpi_hdr.h"

#define BUF_SIZE 10
#define PORT 50002

int main(){
	struct sockaddr_in6 s_addr , c_addr;
	int sfd , j;
	ssize_t numRead;
	socklen_t len;
	char buf[BUF_SIZE];
	char c_addr_str[INET6_ADDRSTRLEN];

	if( (sfd = socket(AF_INET6 , SOCK_DGRAM , 0)) == -1 ){
		perror("socket create error\n");
		exit(1);
	}

	memset(&s_addr , 0 , sizeof(struct sockaddr_in6));
	s_addr.sin6_family = AF_INET6;
	s_addr.sin6_addr = in6addr_any;
	s_addr.sin6_port = htons(PORT);

	if( bind(sfd , (struct sockaddr *) &s_addr , sizeof(struct sockaddr_in6)) == -1){
		perror("bind error\n");
		exit(1);
	}

	memset(&c_addr , 0 , sizeof(struct sockaddr_in6));

	for(;;){
		len = sizeof(struct sockaddr_in6);
		if( (numRead = recvfrom(sfd , buf , BUF_SIZE , 0 , (struct sockaddr *)&c_addr , &len)) == -1){
			perror("recvfrom error\n");
			exit(1);
		}

		if( (inet_ntop(AF_INET6 , &c_addr.sin6_addr , c_addr_str , INET6_ADDRSTRLEN)) == NULL){
			perror("can not translate address\n");
			exit(1);
		}
		else{
			printf("server received %ld bytes from (%s , %u)\n" , (long) numRead , c_addr_str , ntohs(c_addr.sin6_port));
		}

		for(int i=0 ; i<numRead ; i++){
			buf[i] = toupper((unsigned char)buf[i]);
		}

		if( sendto(sfd , buf, numRead , 0 , (struct sockaddr *) &c_addr , sizeof(struct sockaddr_in6)) ==-1){
			perror("sendto error\n");
			exit(1);
		}



	}


	return 0;
}