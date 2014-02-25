#ifndef MYUSART_H
#define MYUSART_H

#include "stm32f10x.h"

enum packet_type_e {
    PACKET_TYPE_QUAT = 0,
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_GYRO,
    PACKET_TYPE_PAUSE,
    PACKER_TYPE_RUN,
    PACKET_TYPE_RESTART,
    PACKET_TYPE_ENGYROCAL,
    PACKET_TYPE_DISGYRPCAL
};



void MyUsart_Config(int rate);
void MyUsart_SendPacket(char packet_type,const void *data);
void MyUsart_Send(const u8 *buf,u8 len);
void HandleOneByte(u8 byte);
void FrameCompleted(const u8 *buf,u8 len);

#endif
