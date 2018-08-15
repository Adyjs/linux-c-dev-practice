#include <stdio.h>
#include <wiringPi.h>



int main(){
	if( wiringPiSetup() == -1){
		perror("wiringPi setup error\n");
		return 1;
	}
	int red_led = 1;

	pinMode( red_led , OUTPUT);
	digitalWrite(red_led , 1);
	return 0;
}
