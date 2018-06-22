/*
Homework : 程式目標 , 讀取某一個檔案的內容，然後轉存到 ./ 目錄下的一個檔案中
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char lowerToCapital(char c){
	if( c >= 'a' && c <= 'z'){
		return (c-32);
	}
	return c;
}

void readAndWrite(FILE *sourceFile , FILE *destFile , char (*callback)(char)){
	char c;
	while( ( c = getc(sourceFile) ) != EOF ){
		//printf("%c" , c);
		fputc( (*callback)(c) , destFile);
	}
	return;
}

FILE *openFile(char *fileName , char *mode){
	FILE *filePtr;
	if( filePtr = fopen(fileName , mode) ){
		return filePtr; 
	}
	printf("%s  open failed.\n" , fileName);
	exit(1);
}

void scan(char *dirName , char *fileName){
	DIR *dirPtr;
	struct dirent *ptr;
	if( dirPtr = opendir(dirName) ){
		while( ptr = readdir(dirPtr)){
			if( strcmp( fileName , ptr->d_name ) == 0 ){
				printf("%s exist\n",ptr->d_name);
				return;
			}
		}
		printf("%s not exist\n" , ptr->d_name);
		return;
	}
	printf("%s open failed\n" , dirName);
	exit(1);
}

void createNew(char *fileName){
	if( fopen(fileName , "a") ){
		printf("%s has been created.\n" , fileName);
		return ;
	}
	printf("new file create failed.\n");
	exit(1);
}

int main(){
	char *newFile = "new_file";
	char *targetFile = "targetFile";
	char *dirName = ".";
	createNew(newFile);
	
	//scan(dirName , targetFile);
	readAndWrite( openFile(targetFile , "r") , openFile(newFile , "w") , lowerToCapital);
	return 0;
}
