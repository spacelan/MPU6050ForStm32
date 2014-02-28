#ifndef MYUSART_H
#define MYUSART_H

#include "stm32f10x.h"

enum packet_type_e {
    PACKET_TYPE_QUAT = 0,
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_GYRO,
    PACKET_TYPE_PAUSE,
    PACKER_TYPE_RUN,
    PACKET_TYPE_RESTART
};



void myUsart_Config(int rate);
void send_packet(char packet_type, void *data);
void myUsartSend(u8 *buf,u8 len);
void handleOneByte(u8 byte);
void frameCompleted(u8 buf[],u8 len);

#endif
