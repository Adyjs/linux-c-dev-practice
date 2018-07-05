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

	printf("\nmask set , SIGINT has been blocking for 5 seconds from now\n");
	sigemptyset(&block);
	sigaddset(&block , SIGINT);
	sigprocmask(SIG_BLOCK , &block , &origin);
	
	sleep(5);
	
	printf("\nmask reset , SIGINT has been unblocking now.\n");
	sigprocmask(SIG_SETMASK , &origin , NULL);
	
	for(;;){}
	return 0;
}
