flags = -Wall -g -o

normal:normal.c reset
	gcc -Wall -g -o normal normal.c -lwiringPi

reset:reset.c busy
	gcc -Wall -g -o reset reset.c -lwiringPi

busy:busy.c
	gcc $(flags) busy busy.c -lwiringPi
