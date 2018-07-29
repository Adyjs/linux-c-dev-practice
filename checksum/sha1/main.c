#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/sha.h>

#define BITS_BLOCK 512
#define PATH "Md5CheckerCn.exe"



int main(int argc , char *argv[]){
	int fd;
	char buf[BITS_BLOCK];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	size_t numRead;

	memset(buf , 0 , BITS_BLOCK);
	
	if( (fd = open(PATH , O_RDONLY)) == -1){
		perror("open error\n");
		exit(1);
	}

	SHA256_CTX sha256;
	SHA256_Init(&sha256);

	while( (numRead = read(fd , buf , BITS_BLOCK)) != 0 ){
		SHA256_Update(&sha256 , buf , numRead);
	}
	SHA256_Final(hash , &sha256);


	for(int i=0 ; i<SHA256_DIGEST_LENGTH ; i++){
		printf("%02X" , hash[i]);
	}
	printf("\t%s\n" , PATH);
	close(fd);
	exit(EXIT_SUCCESS);
}