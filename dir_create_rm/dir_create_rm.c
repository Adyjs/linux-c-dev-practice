#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


void dirRm(char *dir){
	if(rmdir(dir) == 0){
		printf("%s remove success\n" , dir);
		return;
	}
	else{
		printf("%s remove failed\n" , dir);
		exit(1);
	}
}

void filePathReset(char *file){
	if( memset( file , 0 , sizeof(file) ) ){
		printf("file path reset success\n");
		//dirRm(file);
		return;
	}
	else{
		printf("file path reset failed.\n");
		exit(1);
	}
}


void fileRm(char *file){
	if(remove(file) == 0){
		printf("%s : remove success\n" , file);
		filePathReset(file);
		return;
	}
	else{
		printf("%s : remove failed\n" , file);
		exit(1);
	}
}

char* filePathChange(char* buf ,char* path ,char* targetFile){
	if( strcpy(buf , path) ){
		if( strcat(buf , "/") ){
			if( strcat(buf , targetFile) ){
				return buf;
			}
			printf("strcat stage 2 failed.\n");
			exit(1);
		}
		printf("strcat stage 1 failed,\n");
		exit(1);
	}  
	printf("strcpy stage failed.\n");
	exit(1);
}

void scan(char *buf , char *DIR_NAME , char *path){
	struct dirent *ptr;
	DIR *dirPtr;
	int remove_result;
	if( dirPtr = opendir(DIR_NAME) ){
		while( (ptr = readdir(dirPtr)) != NULL ){
			if( strcmp( ptr->d_name , ".") == 0 || strcmp( ptr->d_name , "..") == 0 ){
				continue;
			}
			filePathChange(buf , DIR_NAME , ptr->d_name );
		}
	}
	return;
}

void touch(char *file){
	char *mode = "a";
	if(	fopen( file , mode)){
		printf("create file success\n");
		return;
	}
	printf("create file failed\n");
	exit(1);
}

void authSettingAndTest(char *dirName){
	if( chmod(dirName , S_IRUSR | S_IWUSR | S_IXUSR) == 0 ){
		printf("auth setting success\n");
		int authTest_1 =  access( dirName , R_OK | W_OK | X_OK | F_OK );
		int authTest_2 = access( dirName , R_OK | W_OK | X_OK );
		if( authTest_1 == 0 || authTest_2 == 0  ){
			printf("auth test check pass.\n");
			return;
		}
		printf("auth test check failed.\n");
		exit(1);
	}
	printf("auth setting failed\n");
	exit(1);
}

void createDir(char *dirName){
	if( mkdir( dirName , O_RDWR | O_CREAT) == 0 ){
		printf("%s create success.\n" , dirName);
		authSettingAndTest(dirName);
		return;
	}
	printf("%s create failed.\n" , dirName);
	exit(1);
}

int main(){
	char *DIR_NAME = "target_dir";
	char *file_name_1 = "file_1";
	char *file_name_2 = "file_2";
	char buf[255];
	DIR *dirPtr;
	struct dirent *dir;
	
	createDir(DIR_NAME);
	
	filePathChange(buf , DIR_NAME , file_name_1);
	touch(buf);
	filePathReset(buf);
	
	filePathChange(buf , DIR_NAME , file_name_2);
	touch(buf);
	filePathReset(buf);
	
	scan(buf , DIR_NAME , file_name_1 );
	fileRm(buf);
	
	scan(buf , DIR_NAME , file_name_1 );
	fileRm(buf);

	dirRm(DIR_NAME);
	
	return 0;
}
