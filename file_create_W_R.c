#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *FILE_NAME = "./target.txt";
	char *INITIAL_MODE = "a";
	char *R_MODE = "r";
	FILE *fp = NULL;

	char *input_content = "test content";
	if( (fp = fopen(FILE_NAME , INITIAL_MODE)) ){
		
		//after success create a not exist file .
		
		int input_text_num = 0;
		input_text_num = fwrite(input_content , 1 , strlen(input_content) , fp );
		fclose(fp);

		if(input_text_num){

			//after success write "input_content" string into target file
			//then , close the file.

			if( (fp = fopen(FILE_NAME , R_MODE)) ){

				//after close the file , then open the file again,
				//and read content of target file , 
				//fread will return the read content to a space ,
				//so , we need to allocate a char heap space for the read content

				int read_num = 0;
				char *read_content = malloc(strlen(input_content));
				read_num = fread(read_content , 1 , strlen(input_content) , fp );
				if(read_num){

					// after all step success , just print out the read_content 
					// from allocate space with a pointer

					printf("%s\n" , read_content);
					return 0;
				}
				else{
					printf("read_num : %d\n" , read_num);
					return 1;
				}
			}
			else{
				printf("fopen in read stage failed.\n");
				return 1;
			}
		}
		else{
			printf("fwrite in failed.\n");
			return 1;
		}
	}
	else{
		printf("file create failed.\n");
		return 1;
	}
	return 0;
}
