姿态获取与显示系统下位机
==
基于STM32和MPU6050
--
通过串口与上位机通信
--
115200波特率 8数据位 无校验 1停止位

数据包格式
--
0xAA 0x55 dataLength dataType data[0] data[1]... 

