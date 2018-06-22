#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 20480

void output(FILE *dest, int line , char **arrIP){
	for(int i=0 ; i<line ; i++){
		fwrite(*(arrIP+i) , sizeof(char) , strlen(*(arrIP+i)) , dest);
		fwrite("\n" , sizeof(char) , 1 , dest);
	}
}

void get_IPv4_field(char *dest , char const *source){
	char c;
	int count = 0;
	while( (c = *(source + count) ) != '.'){
		*(dest + (count++)) = c;
	}
	*(dest + count) = '\0';
}


int compar(const void *a , const void *b){
	/*
	char const *strA = *((const char **) a);
	char const *strB = *((const char **) b);
	*/
	char tempA[4];
	char tempB[4];
	get_IPv4_field(tempA , *((const char **) a));
	get_IPv4_field(tempB , *((const char **) b));
	int intA = atoi(tempA);
	int intB = atoi(tempB);
	if(intA > intB){
		return 1;
	}
	if(intA < intB){
		return -1;
	}
	return 0;
}

void display(char **arr , int size){
	printf("\t**display**\n");
	for(int i=0 ; i<size ; i++){
		printf("\t%s\n" , *(arr+i) );
	}
	printf("\n");
	return;
}


char ** analysis(char *content ,int size , int *line){
	/*get quantity of IPv4 by detect '\n' in each line*/
	for(int i=0 ; i<size ; i++){
		if(content[i] == '\n'){
			(*line)++;
		}
	}
	char **arrIP = malloc((*line) * sizeof(char *));
	char *token;
	char *delimiter = "\n";
	int count = 0;
	
	token = strtok(content , delimiter);
	while(token != NULL){
		arrIP[count]= token;
		token = strtok(NULL , delimiter);
		count++;
	}
	display(arrIP , *line);
	qsort(arrIP , (*line) , sizeof(char **) , compar );
	display(arrIP , *line);
	return arrIP;
}

int main(int argc , char *argv[]){
	/*create new file*/
	char *filename = argv[1];
	FILE *new_file = fopen(filename , "w+");
	
	/*open raw file*/
	FILE *raw_file = fopen("./random-IPv4-list" , "r");
	
	/*read content of raw_file and store it into buf*/
	char *buf = malloc(BUFSIZE * sizeof(char));
	size_t read_num;
	char ** arrIP;
	int *line = malloc(sizeof(int));
	*line = 0;
	read_num = fread(buf , sizeof(char) , BUFSIZE , raw_file);
	arrIP = analysis(buf , read_num , line);
	output(new_file , *line , arrIP);
	printf("line : %d\n" , *line);
	fclose(new_file);
	fclose(raw_file);
	return 0;
}


