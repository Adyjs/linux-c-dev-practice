#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>

#define TIME 50
int gpio_0 = 0;
int gpio_1 = 1;
int gpio_2 = 2;

void handler(int sig){
	digitalWrite(gpio_0 , 0);
	digitalWrite(gpio_1 , 0);
	digitalWrite(gpio_2 , 0);
	exit(1);
}

int main(){
	if( wiringPiSetup() == -1){
		perror("wiringPi setup error\n");
		return 1;
	}
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if( sigaction(SIGINT , &sa , 0) == -1){
		perror("sigaction error\n");
		exit(1);
	}

	gpio_0 = 0;
	gpio_1 = 1;
	gpio_2 = 2;
	pinMode(gpio_0 , OUTPUT);
	pinMode(gpio_1 , OUTPUT);
	pinMode(gpio_2 , OUTPUT);
	
	while(1){
		digitalWrite(gpio_0 , 1);
		digitalWrite(gpio_1 , 0);
		digitalWrite(gpio_2 , 0);
		delay(5000);
		
		digitalWrite(gpio_0 , 0);
		digitalWrite(gpio_1 , 1);
		digitalWrite(gpio_2 , 0);
		delay(10000);
		
		for(int i=0 ; i<10 ; i++){
			digitalWrite(gpio_1 , 1);
			delay(200);
			digitalWrite(gpio_1 , 0);
			delay(200);
		}

		digitalWrite(gpio_0 , 0);
		digitalWrite(gpio_1 , 0);
		digitalWrite(gpio_2 , 1);
		delay(3000);

	}
	return 0;
}
