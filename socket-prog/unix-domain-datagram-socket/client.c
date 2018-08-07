#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>


#define BUF_SIZE 10
#define PATH "/home/adyjs/practice/socket-prog/unix-domain-datagram-socket/socket_file"


int main(int c ,char *v[]){
	struct sockaddr_un s_addr , c_addr;
	size_t msg_len;
	ssize_t numRead;
	int sfd;
	char response_buf[BUF_SIZE];

	if( c < 2 || strcmp(v[1] , "--help") == 0){
		perror("cli input error\n");
		exit(1);
	}

	if( (sfd = socket(AF_UNIX , SOCK_DGRAM , 0)) == -1){
		perror("socket error\n");
		exit(1);
	}

	memset(&c_addr , 0 , sizeof(struct sockaddr_un));
	c_addr.sun_family = AF_UNIX;
	//strncpy(c_addr.sun_path , PATH , sizeof(c_addr.sun_path)-1 );
	snprintf(c_addr.sun_path , sizeof(c_addr.sun_path) , "/home/adyjs/practice/socket-prog/unix-domain-datagram-socket/%d" , getpid());

	if( bind(sfd , (struct sockaddr *) &c_addr , sizeof(struct sockaddr_un)) == -1){
		perror("c_addr binding error\n");
		exit(1);
	}

	memset(&s_addr , 0 , sizeof(struct sockaddr_un));
	s_addr.sun_family = AF_UNIX;
	strncpy(s_addr.sun_path , PATH , sizeof(s_addr.sun_path)-1 );
	
	for(int i=1 ; i<c ; i++){
		int act_send;
		msg_len = strlen(v[i]);
		printf("msg_len : %d\n" , msg_len);
		if( (act_send = sendto(sfd , v[i]  , msg_len , 0 , (struct sockaddr *) &s_addr , sizeof(struct sockaddr_un))) != msg_len){
			printf("act_send : %d\n" , act_send);
			perror("msg send error\n");
			exit(1);
		}
		if( (numRead = recvfrom(sfd , response_buf , BUF_SIZE , 0 , NULL , NULL )) == -1){
			perror("recv error\n");
			exit(1);
		}
		printf("response %d : %.*s\n" , i , numRead , response_buf);
	}

	remove(c_addr.sun_path);

	exit(EXIT_SUCCESS);
}