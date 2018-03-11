#include "delay.h"

void delay(int duration)
{
	int volatile delay;
	delay = 0;
	while(delay < duration) {
		++delay;
	}
}
