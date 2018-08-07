#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>

#define PORT 50000
#define BUF 100

int main(int argc , char *argv[]){
	int sock_fd;
	struct sockaddr_in s_addr , c_addr;
	socklen_t c_addr_len;
	short port = 50000;
	ssize_t numRead;
	char buf[BUF];
	char c_addr_str[INET_ADDRSTRLEN];

	if( (sock_fd = socket(AF_INET , SOCK_DGRAM , 0))== -1){
		perror("socket error\n");
		exit(1);
	}

	memset(&s_addr , 0 , sizeof(struct sockaddr_in));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	
	if( inet_pton(AF_INET , "0.0.0.0" , &s_addr.sin_addr) == -1){
		perror("inet_pton error\n");
		exit(1);
	}

	if( bind(sock_fd , (struct sockaddr *) &s_addr , sizeof(struct sockaddr_in)) == -1){
		perror("bind error\n");
		exit(1);
	}

	for(;;){
		c_addr_len = sizeof(struct sockaddr_in);
		if( (numRead = recvfrom(sock_fd , buf , BUF , 0 ,(struct sockaddr *) &c_addr , &c_addr_len)) == -1 ){
			perror("recvfrom error\n");
			exit(1);
		}

		if( inet_ntop(AF_INET , &c_addr.sin_addr , c_addr_str , INET_ADDRSTRLEN) == NULL ){
			perror("inet_ntop error\n");
			exit(1);
		}
		else{
			printf("server received %d bytes from %s : %u\n" , numRead , c_addr_str , ntohs(c_addr.sin_port));
		}

		for(int i=0 ; i<numRead ; i++){
			if(i%2 == 0){
				buf[i] = toupper((unsigned char) buf[i]);
			}
			else{
				buf[i] = tolower((unsigned char) buf[i]);
			}
		}

		if( sendto(sock_fd , buf , numRead , 0 ,(struct sockaddr *) &c_addr , sizeof(struct sockaddr_in)) != numRead){
			perror("sendto error\n");
			exit(1);
		}
	}
}