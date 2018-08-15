#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <signal.h>

#define DELAY 50

int gpio_1_red;

static void handler(int sig){
	digitalWrite(gpio_1_red , 1);
	exit(1);
}


int main(){
	if( wiringPiSetup() == -1){
		perror("wiringPi setup error\n");
		return 1;
	}
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;

	if(sigaction(SIGINT , &sa , NULL) == -1){
		perror("sigaction error\n");
		return 1;
	}

	gpio_1_red = 1;
	pinMode(gpio_1_red , OUTPUT);
	while(1){
		digitalWrite(gpio_1_red , 1);
		delay(DELAY);
		digitalWrite(gpio_1_red , 0);
		delay(DELAY);
	}
	return 0;
}
