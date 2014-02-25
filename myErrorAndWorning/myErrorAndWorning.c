#include "myErrorAndWorning.h"
#include "myled.h"
#include "delay.h"

void MyError(u8 n)
{
	u8 t = n;
	while(1)
	{
		while(t--)
		{
			MyLED(ON);
			Delay_ms(50);
			MyLED(OFF);
			Delay_ms(100);
		}
		Delay_ms(1000 - 150 * n);
		t = n;
	}
}

void MyWorning(void)
{
	MyLED(ON);
	Delay_ms(500);
	MyLED(OFF);
}
