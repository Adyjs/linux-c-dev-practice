#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void handler(int sig){
	printf("caught a sig : %d\n" , sig);
	return ;
}
int main(){
	signal(SIGINT , handler);

	sigset_t origin , block;

	printf("\nmask set , SIGINT will be block in 5 sec\n");
	sigemptyset(&block);
	sigaddset(&block , SIGINT);
	sigprocmask(SIG_BLOCK , &block , &origin);
	
	sleep(5);
	
	printf("\nmask reset , SIGINT is been unblocked\n");
	sigprocmask(SIG_SETMASK , &origin , NULL);
	
	for(;;){}
	return 0;
}
