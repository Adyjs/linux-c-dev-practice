#include <stdio.h>
#include <stdlib.h>


char *s1 = "12345";
char *s2 = "987654321";

void _malloc(char **ptr , size_t len , size_t base){
	if( (*ptr = malloc(len * base) ) == NULL ){		//malloc for temperary copy space
		perror("malloc failed\n");
		exit(1);
	}
}

void rev(char **str)
{
	size_t len = 0;
	char *temp = NULL;

	while( *(*str+len) != '\0'){		//get length of str
		len++;
	}

	_malloc(&temp , len ,sizeof(char));
	
	for(size_t i=0 ; i<len ; i++){		//reverse copy from str to temp
		*(temp+i) = *( (*str)+(len-i-1) );
	}

	_malloc(str , len , sizeof(char));
	
	for(size_t i=0 ; i<len ; i++){		//copy back to str memory allocated space
		*((*str)+i) = *(temp+i);
	}

	free(temp);
}

int main(){
	printf("before rev : %s , %s\n" , s1 , s2);
	rev(&s1);
	rev(&s2);
	printf("after rev : %s , %s\n" , s1 , s2);
}
