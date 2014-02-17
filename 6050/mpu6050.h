#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f10x.h"
#define BYTE u8
#define q30  1073741824.0f
void MPU_Config(void);
void get_sensors(void);
#endif
