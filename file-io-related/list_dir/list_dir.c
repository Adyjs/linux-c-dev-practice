
/*
Homework : 程式目標，撰寫一程式能列表出當下目錄的所有檔案及目錄，類似 ls 的功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(){
	char *dirName = ".";
	DIR *dirPtr;
	struct dirent *ptr;
	if( dirPtr = opendir(dirName) ){
		while( ptr = readdir(dirPtr) ){
			printf("%s    " , ptr->d_name);
		}
		printf("\n");
		return 0;
	}
	printf("cannot open the directory \"%s\" \n" , dirName);
	return 0;
}

