#include <stdio.h>
#include <stdlib.h>

static int FIXED_PRE_BLANK = 5;
void star(int num);
void blank(int num);
void up_down_border(int num);
void side_border(int num);
void fixed_preblank(int num);
void box(int width , int height);


int main(int argc , char *argv[]){
	if(argc != 3 ){
		//perror("input error\n");
		printf("input error\n");
		printf("input form : %s %s %s\n" , argv[0] , "width" , "height");
		return 1;
	}
	box(atoi(argv[1] ), atoi(argv[2]));
	return 0;
}

void box(int width , int height){
	up_down_border(width);
	for(int i=0 ; i<height ; i++){
		side_border(width);
	}
	up_down_border(width);
	return;
}

void side_border(int num){
	fixed_preblank(FIXED_PRE_BLANK);
	printf("*");
	blank(num-2);
	printf("*\n");
	return;
}

void up_down_border(int num){
	fixed_preblank(FIXED_PRE_BLANK);
	star(num);
	return;
}

void fixed_preblank(int num){
	for(int i=0 ; i<num ; i++){
		printf(" ");
	}
	return;
}

void star(int num){
	for(int i=0 ; i<num ; i++){
		printf("*");
		if(i == num-1){
			printf("\n");
			return;
		}
	}
}

void blank(int num){
	for(int i=0 ; i<num ; i++){
		printf(" ");
	}
}
