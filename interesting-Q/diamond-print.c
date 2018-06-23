#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void odd_diamond(int const n){
	// int s = (n*2)-1;
	// int e = (n-s)/2;
	int s , e , line;
	line = (n/2)+1;
	for(int i=1 ; i<=line ; i++){
		s = (i*2) - 1;
		e = (abs(n-s))/2;
		//printf("s:%d , n:%d\n" , s , e);
		for(int j=0 ; j<e ; j++){
			printf(" ");
		}
		for(int k=0 ; k<s ; k++){
			printf("*");
		}
		printf("\n");
	}
	for(int i=(line-1) ; i>0 ; i--){
		s = (i*2) - 1;
		e = (abs(n-s))/2;
		//printf("s:%d , n:%d\n" , s , e);	
		for(int j=0 ; j<e ; j++){
			printf(" ");
		}
		for(int k=0 ; k<s ; k++){
			printf("*");
		}
		printf("\n");
	}
}

void even_diamond(int const n){
	for(int i=1 ; i<=n ; i++){
		int e = n-i;
		int s = i;
		int ee = s-1;
		for(int j=0 ; j<e ; j++){
			printf(" ");
		}
		for(int k=0 ; k<s ; k++){
			printf("*");
			if(ee){
				printf(" ");
				ee--;
			}
		}
		printf("\n");
	}
	for(int i=n-1 ; i>0 ; i--){
		int e = n-i;
		int s = i;
		int ee = s-1;
		for(int j=0 ; j<e ; j++){
			printf(" ");
		}
		for(int k=0 ; k<s ; k++){
			printf("*");
			if(ee){
				printf(" ");
				ee--;
			}
		}
		printf("\n");
	}
}


void switcher(int amount){
	if(amount%2){
		odd_diamond(amount);
	}
	else{
		even_diamond(amount);
	}
	return;
}

int main(){
	switcher(21);
	switcher(20);
}