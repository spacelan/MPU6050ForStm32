#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "myled.h"
#include "myiic.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "math.h"

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

#define q30  1073741824.0f
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
float Pitch,Roll,Yaw;

void myError(void)
{
	while(1)
	{
		myLED(ON);
		delay_ms(50);
		myLED(OFF);
		delay_ms(100);
		myLED(ON);
		delay_ms(50);
		myLED(OFF);
		delay_ms(800);
	}
}

int main()
{
    int result;
    unsigned char accel_fsr;
    unsigned short gyro_rate, gyro_fsr;
    unsigned long timestamp;

	SystemInit();
	NVIC_Configuration();
	myLED_GPIO_Config();
	i2cInit();
	delay_init(72);
//	result = mpu_init();
	mpu_init() == 0 ? 1 : myError();
	mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : myError();
	mpu_configure_fifo(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : myError();
	mpu_set_sample_rate(DEFAULT_MPU_HZ) == 0 ? 1 : myError();

    dmp_load_motion_driver_firmware() == 0 ? 1 : myError();
    dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL) == 0 ? 1 : myError();
    dmp_set_fifo_rate(DEFAULT_MPU_HZ) == 0 ? 1 : myError();

//TODO    run_self_test();
    mpu_set_dmp_state(ENABLE) == 0 ? 1 : myError();

	while(1)
	{
		unsigned long sensor_timestamp;
		short gyro[3], accel[3], sensors;
		unsigned char more;
		long quat[4];
		//float Yaw,Roll,Pitch;
		dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);
		/* Gyro and accel data are written to the FIFO by the DMP in chip
		* frame and hardware units. This behavior is convenient because it
		* keeps the gyro and accel outputs of dmp_read_fifo and
		* mpu_read_fifo consistent.
		*/
		/*     if (sensors & INV_XYZ_GYRO )
		send_packet(PACKET_TYPE_GYRO, gyro);
		if (sensors & INV_XYZ_ACCEL)
		send_packet(PACKET_TYPE_ACCEL, accel); */
		/* Unlike gyro and accel, quaternions are written to the FIFO in
		* the body frame, q30. The orientation is set by the scalar passed
		* to dmp_set_orientation during initialization.
		*/
		if (sensors & INV_WXYZ_QUAT )
		{
			q0=quat[0] / q30;
			q1=quat[1] / q30;
			q2=quat[2] / q30;
			q3=quat[3] / q30;
			Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch
			Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
			Yaw = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
		}
		if(sensors & INV_XYZ_GYRO)
		{}
		if(sensors & INV_XYZ_ACCEL)
		{}
		//send_packet(PACKET_TYPE_QUAT, quat);
	}
	while(1)
	{

		myLED(ON);
		delay_ms(100);
		myLED(OFF);
		delay_ms(900);
	}
}
