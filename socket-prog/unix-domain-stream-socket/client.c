#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define PATH "/tmp/fuck_socket"
#define BACKLOG 5

int main(){
	struct sockaddr_un addr;
	int sfd;
	ssize_t numRead;
	char buf[BUF_SIZE];
	printf("c1\n");
	if( (sfd = socket(AF_UNIX , SOCK_STREAM , 0)) == -1 ){
		perror("socket error\n");
		exit(1);
	}
	printf("c2\n");
	memset(&addr , 0 , sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy( addr.sun_path , PATH , sizeof(addr.sun_path)-1  );
	printf("c3\n");
	if( connect(sfd , (struct sockaddr *) &addr , sizeof(struct sockaddr_un)) == -1){
		perror("connect error fuck fuck fuck\n");
		exit(1);
	}
	printf("c4\n");
	while( (numRead = read(STDIN_FILENO , buf , BUF_SIZE)) > 0 ){
		printf("in client numRead : %d\n" , numRead);
		if( write(sfd , buf , numRead) != numRead ){
			perror("reading and writing are not exact\n");
			exit(1);
		}
		break;
	}
	printf("out of read and write , and about to shutdown connection\n");
	sleep(3);
	shutdown(sfd , SHUT_RDWR);
	printf("already shutdown connection\n");
	sleep(10);
	printf("c6\n");
	if(numRead == -1){
		perror("read error\n");
		exit(1);
	}
	printf("c7 , before exit\n");
	sleep(5);

	exit(EXIT_SUCCESS);

}
