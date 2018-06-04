#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 18


void input(FILE *filepath , char *buf){
	//int count = 0;
	fwrite(buf , sizeof(char) , strlen(buf) , filepath);
	//count++;
}

void IPv4_generate(char *buf){
	int count = 0;
	int field;
	char temp[5];
	while(count < 3){
		field = rand() % 256;
		sprintf(temp ,"%d." , field);
		if(count == 0 ){
			strcpy(buf , temp);
		}
		else{
			strcat(buf , temp);
		}
		memset(temp , '\0' , strlen(temp));
		count++;
	}
	field = rand() % 256;
	sprintf(temp , "%d%c%c" , field , '\n' , '\0');
	strcat(buf , temp);
	return;
}

int main(int argc , char *argv[]){
	srand(time(NULL));
	int num = atoi(argv[1]);
	FILE *newfile = fopen("random-IPv4-list" , "w+");
	char buf[BUFSIZE];
	for(int i=0 ; i<num ; i++){
		IPv4_generate(buf);
		input(newfile , buf);
		//printf("%s\n" , buf);
	}
	fclose(newfile);
	return 0;
}

