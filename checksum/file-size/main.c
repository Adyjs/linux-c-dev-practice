#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "Md5CheckerCn.exe"

int main(int argc , char *argv[]){
	FILE *fp;
	size_t bytes;
	if( (fp = fopen(PATH , "r")) == NULL){
		perror("fopen error\n");
		exit(1);
	}

	if( fseek(fp , 0L , SEEK_END) != 0){
		perror("fseek error\n");
		exit(1);
	}

	bytes = ftell(fp);
	printf("file size : %d  bytes , %.1f KB\n" , bytes  , (float) (bytes/1024.0));



	exit(EXIT_SUCCESS);
}