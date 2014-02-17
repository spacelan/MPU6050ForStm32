#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "myled.h"
#include "myiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "myusart.h"

int main()
{
	SystemInit();
	NVIC_Configuration();
	myLED_GPIO_Config();
	i2cInit();
	myUsart_Config(9600);
	delay_init(72);
	//ÉÏµçµÈ´ý
	delay_ms(500);
	MPU_Config();
	while(1)
	{
		get_sensors();
		delay_ms(1000);
	}
}
