#include "myusart.h"
#include "string.h"
void myUsart_Config(int rate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = rate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

void send_packet(char packet_type, void *data)
{
#define MAX_BUF_LENGTH  (18)
    u8 buf[MAX_BUF_LENGTH], length;

    memset(buf, 0, MAX_BUF_LENGTH);
    buf[0] = 0xaa;
    buf[1] = packet_type;

    if (packet_type == PACKET_TYPE_ACCEL || packet_type == PACKET_TYPE_GYRO)
    {
        short *sdata = (short*)data;
        buf[2] = (char)(sdata[0] >> 8);
        buf[3] = (char)sdata[0];
        buf[4] = (char)(sdata[1] >> 8);
        buf[5] = (char)sdata[1];
        buf[6] = (char)(sdata[2] >> 8);
        buf[7] = (char)sdata[2];
        length = 8;
    }
    else if (packet_type == PACKET_TYPE_QUAT)
    {
        long *ldata = (long*)data;
        buf[2] = (char)(ldata[0] >> 24);
        buf[3] = (char)(ldata[0] >> 16);
        buf[4] = (char)(ldata[0] >> 8);
        buf[5] = (char)ldata[0];
        buf[6] = (char)(ldata[1] >> 24);
        buf[7] = (char)(ldata[1] >> 16);
        buf[8] = (char)(ldata[1] >> 8);
        buf[9] = (char)ldata[1];
        buf[10] = (char)(ldata[2] >> 24);
        buf[11] = (char)(ldata[2] >> 16);
        buf[12] = (char)(ldata[2] >> 8);
        buf[13] = (char)ldata[2];
        buf[14] = (char)(ldata[3] >> 24);
        buf[15] = (char)(ldata[3] >> 16);
        buf[16] = (char)(ldata[3] >> 8);
        buf[17] = (char)ldata[3];
        length = 18;
    }



    /* else if (packet_type == PACKET_TYPE_TAP) {
        buf[2] = ((char*)data)[0];
        buf[3] = ((char*)data)[1];
        length = 4;
    } else if (packet_type == PACKET_TYPE_ANDROID_ORIENT) {
        buf[2] = ((char*)data)[0];
        length = 3;
    } else if (packet_type == PACKET_TYPE_PEDO) {
        long *ldata = (long*)data;
        buf[2] = (char)(ldata[0] >> 24);
        buf[3] = (char)(ldata[0] >> 16);
        buf[4] = (char)(ldata[0] >> 8);
        buf[5] = (char)ldata[0];
        buf[6] = (char)(ldata[1] >> 24);
        buf[7] = (char)(ldata[1] >> 16);
        buf[8] = (char)(ldata[1] >> 8);
        buf[9] = (char)ldata[1];
        length = 10;
    } else if (packet_type == PACKET_TYPE_MISC) {
        buf[2] = ((char*)data)[0];
        buf[3] = ((char*)data)[1];
        buf[4] = ((char*)data)[2];
        buf[5] = ((char*)data)[3];
        length = 6;
    }*/
    myUsartSend(buf,length);
}

void myUsartSend(u8 *buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1,buf[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
}
