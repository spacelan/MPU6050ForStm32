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

上位机在这里
--
[https://github.com/spacelan/MyCom-receiveQuat](https://github.com/spacelan/MyCom-receiveQuat)</br>

渣像素
--
![image](https://github.com/spacelan/MPU6050ForStm32/raw/master/IMG_20140222_113035.jpg "image")



