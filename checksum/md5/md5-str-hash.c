#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <openssl/md5.h>

#define PATH "Md5CheckerCn.exe"
#define BIT_SIZE 512


int main(int argc , char *argv[]){
	int fd;
	unsigned char digest[MD5_DIGEST_LENGTH];
	char buf[BIT_SIZE];
	size_t bytes;

	if(argc != 1 ){
		perror("input error\n");
		exit(1);
	}
	memset(buf , 0 , BIT_SIZE);

	if( (fd = open(PATH , O_RDONLY)) == -1){
		perror("open error\n");\
		exit(1);
	}
	

	MD5_CTX context;
	MD5_Init(&context);
	while( (bytes = read(fd , buf , BIT_SIZE)) != 0){
		MD5_Update(&context , buf , bytes);	
	}
	MD5_Final(digest , &context);


	for(int i=0 ; i<MD5_DIGEST_LENGTH ; i++){
		printf("%02X" , digest[i]);
	}
	printf("\t%s\n" , PATH);
	close(fd);
	exit(EXIT_SUCCESS);



}