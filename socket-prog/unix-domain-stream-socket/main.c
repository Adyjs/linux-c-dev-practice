#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>

#define BUF_SIZE 100
#define PATH "/tmp/fuck_socket"
#define BACKLOG 5

int main(){
	struct sockaddr_un addr;
	int sfd , cfd;
	ssize_t numRead;
	char buf[BUF_SIZE];

	if( (sfd = socket(AF_UNIX , SOCK_STREAM , 0)) == -1 ){
		perror("sfd == -1\n");
		exit(1);
	}

	if(remove(PATH) == -1 && errno != ENOENT){
		printf("remove-%s\n" , PATH);
		exit(1);
	}

	memset(&addr , 0 , sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path , PATH , sizeof(addr.sun_path)-1 );

	

	if( bind(sfd ,  (struct sockaddr *)&addr , sizeof(struct sockaddr_un)) == -1){
		perror("bind error\n");
		exit(1);
	}



	if( listen(sfd , BACKLOG) == -1){
		perror("listen error\n");
		exit(1);
	}

	for(;;){
		printf("p1\n");
		if( (cfd = accept(sfd , NULL , NULL)) == -1 ){
			perror("socket accept error\n");
			exit(1);
		}

		printf("p2\n");
		while( (numRead = read(cfd , buf , BUF_SIZE)) >0 ){
			if( write(STDOUT_FILENO , buf , numRead) != numRead ){
				perror("reading and writing are not exact\n");
				exit(1);
			}
		}
		printf("out of while read and write\n");

		if(numRead == -1){
			perror("read error\n");
			exit(1);
		}

		printf("p6\n");
		if(close(cfd) == -1){
			perror("close error\n");
			exit(1);
		}
		printf("last position\n");

	}


	return 0;
}