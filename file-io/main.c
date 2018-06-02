#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 4096


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

 
void flat_char(char *dest , int size  , int line , char **source){
	int count;
	char c;
	for(int i=0 ; i<size ; i++){
		count = 0;
		while( (c = *(*(source+i)+count) ) != '\0'){
			//printf("%c" , c);
			*(dest+count) = c;
			count++;
		}
		//printf("%c\n" , c);
		*(dest+count) = '\n';
	}
	for(int j=0 ; j<size; j++){
		printf("%c", *(dest+j));
	}
}

void analysis(char *content ,int size , int *line){
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
	//char *test = malloc(BUFSIZE * sizeof(char));
	//flat_char(test , size ,  *line , arrIP);
	//return arrIP;
}

int main(int argc , char *argv[]){
	/*create new file*/
	char *filename = argv[1];
	FILE *new_file = fopen(filename , "w+");
	/*open raw file*/
	FILE *raw_file = fopen("./network-ip-list" , "r");
	/*read content of raw_file and store it into buf*/
	char *buf = malloc(BUFSIZE * sizeof(char));
	//char **after_buf;
	size_t read_num;
	int *line = malloc(sizeof(int));
	*line = 0;
	while( (read_num = fread(buf , sizeof(char) , BUFSIZE , raw_file)) != 0 ){
		printf("num : %d , buf : %d\n" , read_num , sizeof(buf));
		analysis(buf , read_num , line);
		/*write the content of buf*/
		fwrite(buf , sizeof(char) , read_num, new_file);
		memset(buf , '\0' , strlen(buf));
	}
	printf("line : %d\n" , *line);
	fclose(new_file);
	fclose(raw_file);
	return 0;
}





/*
int comp(void const *a , void const *b){
	const char *aa = *(const char **)a;
	const char *bb = *(const char **)b;
	return strcmp(bb , aa);
}

void process(char **arrIP ,int arrIP_length ){
	qsort( arrIP , arrIP_length , sizeof(char *) , comp);
}

void analysis(char content[] ,int size , int *line){
	//put every ip into array and sorting

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
		//printf("%s\n" , arrIP[count] );
		token = strtok(NULL , delimiter);
		count++;
	}
	for(int i=0 ; i<(*line) ; i++){
		printf("%d : %s\n" , i+1 , *(arrIP+i) );
	}
	process(arrIP , (*line));
	for(int i=0 ; i<(*line) ; i++){
		printf("%d : %s\n" , i+1 , *(arrIP+i) );
	}

}

*/
