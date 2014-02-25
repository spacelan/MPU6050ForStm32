#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "myled.h"
#include "myiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "myusart.h"
#include "core_cm3.h"

enum myControl_Type
{
	myControl_Type_Pause = 0,
	myControl_Type_Run,
	myControl_Type_Restart,
};

int myState;

int main()
{
	SystemInit();
	NVIC_Configuration();
	MyLED_GPIO_Config();
	I2c_Init();
	MyUsart_Config(115200);
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
	Delay_Init(72);
	//ÉÏµçµÈ´ý
	Delay_ms(10);
	MPU_Config();
	myState = myControl_Type_Pause;
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	while(1)
	{
		while(myState == myControl_Type_Pause) ;
		if(myState == myControl_Type_Restart)
		{
			//NVIC_SETFAULTMASK();
			NVIC_SystemReset();
		}
		MPU_ReadDMPFifo();
		MyUsart_SendPacket(PACKET_TYPE_QUAT,MPU_GetQuatData());
		Delay_ms(50);
	}
}

