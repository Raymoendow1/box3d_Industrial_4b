#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<wiringPi.h>

//#define DEBUG
#define BLUE 0
#define GREEN 2
#define RED 3


void TogglePin(int pin)
{
	int state=0;
	state=!digitalRead(pin);
	digitalWrite(pin, state);
}


int main(int argc, char *args[])
{
	int i, j;
	int GPIO=0;

#ifdef DEBUG
	printf("Argcounter = %d\n\n",argc);
#endif

// Check if input is a number and atleast more then 1 arguments
	if(argc>1)
	{
		for(j=1; j<argc; j++)
			for(i=0; i<sizeof(args[j]);i++)
				if(!isdigit(args[j][0]))
 				{
					printf("arg %d is not a digit\n\n", j);
					return 1;
				}
		}
	else return 1;


	// Setup of wiringPi (before using pinMode), return if setup goes wrong
	if(wiringPiSetup())
	{
		printf("wiringPiSetup Error\n\n");
		return 1;
	}

	// Check for invalid pinnummers
	for(i=1; i<argc; i++)
	{
		GPIO = atoi(args[i]);
		if(GPIO==1||GPIO>3)
		{
			printf("Pinnumber(s) 1 and 3 not supported\n\n");
			return 1;
		}
		pinMode(GPIO, OUTPUT);
	}

	// Execute blinking program loop (do it forever)
	while(TRUE)
	{
		// Toggle all pins
		for(i=1; i<argc; i++) TogglePin(atoi(args[i]));
		delay(500);
	}
	return 0;
}

