#include "myErrorAndWorning.h"
#include "myled.h"
#include "delay.h"

void myError(u8 n)
{
	while(1)
	{
		while(n--)
		{
			myLED(ON);
			delay_ms(50);
			myLED(OFF);
			delay_ms(100);
		}
		delay_ms(1000 - 150 * n);
	}
}

void myWorning(void)
{
	myLED(ON);
	delay_ms(500);
	myLED(OFF);
}
