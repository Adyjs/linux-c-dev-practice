#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <errno.h>

#define BUF_SIZE 10
#define PATH "/home/adyjs/practice/socket-prog/unix-domain-datagram-socket/socket_file"

int main(){
	struct sockaddr_un addr , src_addr;
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	socklen_t len;

	if( (sfd = socket(AF_UNIX , SOCK_DGRAM , 0)) == -1){
		perror("socket create error\n");
		exit(1);
	}

	if( remove(PATH) == -1 && errno != ENOENT){
		perror("PATH error\n");
		exit(1);
	}

	memset( &addr , 0 , sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path , PATH , sizeof(addr.sun_path)-1);

	if(bind( sfd , (struct sockaddr *) &addr , sizeof(struct sockaddr_un)) == -1){
		perror("binding error\n");
		exit(1);
	}

	for(;;){
		len = sizeof(struct sockaddr_un);
		if( (numRead = recvfrom(sfd , buf , BUF_SIZE , 0 , (struct sockaddr *) &src_addr , &len)) == -1 ) {
			perror("recvfrom error\n");
			exit(1);
		}
		printf("server has received %d bytes from %s\n" , numRead , src_addr.sun_path);
		for(int i=0 ; i<numRead ; i++){
			buf[i] = toupper((unsigned char)buf[i]);
		}

		if( sendto(sfd , buf , numRead , 0 , (struct sockaddr *) &src_addr , len) != numRead){
			perror("sendto error\n");
			exit(1);
		}

	}





}



