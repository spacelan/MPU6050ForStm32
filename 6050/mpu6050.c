#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "myErrorAndWorning.h"

static struct
{
	volatile short gyro[3],accel[3];
	volatile long quat[4];
	volatile unsigned long timeStamp;
	volatile short sensors;
}MPUSensorData;

/*********************************************************************
*Function: run_self_test
*Description: MPU6050自测
*Description: 设定bias
*Input:
*Output:
*Return:
*Others:
*Author: Spacelan
*Date: 2014-2-25
*********************************************************************/
static inline void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x03) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] = (long)(accel[0] * accel_sens);
        accel[1] = (long)(accel[1] * accel_sens);
        accel[2] = (long)(accel[2] * accel_sens);
        dmp_set_accel_bias(accel);
    }

    /* Report results. */
/*    test_packet[0] = 't';
    test_packet[1] = result;
    send_packet(PACKET_TYPE_MISC, test_packet);
*/
}

/*********************************************************************
*Function: MPU_Config
*Description: 配置MPU6050
*Description: 载入DMP firmware
*Description: 进行自测
*Input:
*Output:
*Return:
*Others:
*Author: Spacelan
*Date: 2014-2-25
*********************************************************************/
void MPU_Config(void)
{
	mpu_init() == 0 ? 1 : MyError(1);
	mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : MyError(2);
//	mpu_configure_fifo(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : myError(3);
	mpu_set_sample_rate(500) == 0 ? 1 : MyError(4);

    dmp_load_motion_driver_firmware() == 0 ? 1 : MyError(5);
    dmp_enable_feature(  DMP_FEATURE_6X_LP_QUAT
    					|DMP_FEATURE_GYRO_CAL
    					//|DMP_FEATURE_SEND_CAL_GYRO
    					|DMP_FEATURE_SEND_RAW_GYRO
    					|DMP_FEATURE_SEND_RAW_ACCEL
    					) == 0 ? 1 : MyError(6);
    dmp_set_fifo_rate(50) == 0 ? 1 : MyError(7);
    mpu_set_dmp_state(ENABLE) == 0 ? 1 : MyError(8);
    run_self_test();
}

/*********************************************************************
*Function: MPU_ReadDMPFifo
*Description: 读取DMP fifo
*Description: 将数据存入MPUSensorData结构中
*Input:
*Output:
*Return:
*Others:
*Author: Spacelan
*Date: 2014-2-25
*********************************************************************/
void MPU_ReadDMPFifo(void)
{
    unsigned char more;
    while(dmp_read_fifo(MPUSensorData.gyro, MPUSensorData.accel,
    		MPUSensorData.quat, &MPUSensorData.timeStamp, &MPUSensorData.sensors,
    		&more) || more);
}

/*********************************************************************
*Function: MPU_GetQuatData
*Description: 获取四元数数据，返回指向四元数数组的指针
*Input:
*Output:
*Return: MPUSensorData.quat
*Others:
*Author: Spacelan
*Date: 2014-2-25
*********************************************************************/
void *MPU_GetQuatData(void)
{
	return MPUSensorData.quat;
}
