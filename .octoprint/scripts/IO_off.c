#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<wiringPi.h>

#define DEBUG
#define BLUE 0
#define GREEN 2
#define RED 3


int main(int argc, char *args[])
{
	int i, j, GPIO, state;

#ifdef DEBUG
	printf("Argcounter = %d\n\n",argc);
#endif

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

	for(i=1; i<argc; i++)
	{
		GPIO = atoi(args[i]);

		if(GPIO==1||GPIO>3)
		{
			printf("Pinnumbers not supported\n\n");
			return 1;
		}
		if(i<=1)
			if(wiringPiSetup()) return 1;

//		state = !digitalRead(GPIO);
		state = LOW; //Don't toggle, always putout HIGH or LOW
		pinMode (GPIO, OUTPUT) ;
		digitalWrite(GPIO, state);

#ifdef DEBUG
		printf("GPIO - %d\t", GPIO);
		if(state) printf("on\n\n");
		else printf("off\n\n");
#endif
	}
	return 0;
}

