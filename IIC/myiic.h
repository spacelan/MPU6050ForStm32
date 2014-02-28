#ifndef __STM32_I2C_H
#define __STM32_I2C_H
//#include "define.h"
#include "stm32f10x.h"

//typedef bool char;
//
//#define false    0
//#define	true     1

#define CLI()      __set_PRIMASK(1)  
#define SEI()      __set_PRIMASK(0)

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define true 1
#define false 0 
typedef int8_t bool;

/*
#define MPU6050_READRATE			1000	//6050读取频率
#define MPU6050_READTIME			0.001	//6050读取时间间隔
#define EE_6050_ACC_X_OFFSET_ADDR	0
#define EE_6050_ACC_Y_OFFSET_ADDR	1
#define EE_6050_ACC_Z_OFFSET_ADDR	2
#define EE_6050_GYRO_X_OFFSET_ADDR	3
#define EE_6050_GYRO_Y_OFFSET_ADDR	4
#define EE_6050_GYRO_Z_OFFSET_ADDR	5
*/
//0表示写
#define	I2C_Direction_Transmitter   0
//１表示读
#define	I2C_Direction_Receiver      1	 
/*====================================================================================================*/
/*====================================================================================================*/
//bool i2cWriteWords(uint8_t addr, uint8_t reg, uint8_t len, uint16_t* data);
//bool i2cWriteWord(uint8_t addr, uint8_t reg, uint16_t data);
bool i2cWriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t const *buf);
//bool i2cWriteBits(uint8_t addr, uint8_t reg, uint8_t bitNum, uint8_t len, uint8_t data);
//bool i2cWriteBit(uint8_t addr, uint8_t reg, uint8_t bitNum, uint8_t data);
bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t const *data);

bool i2cReadBuffer(uint8_t addr_, uint8_t reg_, uint8_t len, uint8_t* buf);
//bool i2cReadBits(uint8_t addr, uint8_t reg, uint8_t bitNum, uint8_t len, uint8_t *data, uint16_t *timeout);
//bool i2cReadBit(uint8_t addr, uint8_t reg, uint8_t bitNum, uint8_t *data, uint16_t *timeout);
bool i2cRead(uint8_t addr, uint8_t reg, uint8_t *data);

void i2cInit(void);

bool i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t const *buf);
bool i2cread(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
/*====================================================================================================*/
/*====================================================================================================*/
#endif

