#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "myErrorAndWorning.h"
#include "myusart.h"
#include "math.h"
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

void MPU_Config(void)
{
	mpu_init() == 0 ? 1 : myError(1);
	mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : myError(2);
//	mpu_configure_fifo(INV_XYZ_ACCEL | INV_XYZ_GYRO) == 0 ? 1 : myError(3);
	mpu_set_sample_rate(200) == 0 ? 1 : myError(4);

    dmp_load_motion_driver_firmware() == 0 ? 1 : myError(5);
    dmp_enable_feature(  DMP_FEATURE_6X_LP_QUAT
    					|DMP_FEATURE_GYRO_CAL
    					|DMP_FEATURE_SEND_CAL_GYRO
    					|DMP_FEATURE_SEND_RAW_ACCEL
    					) == 0 ? 1 : myError(6);
    dmp_set_fifo_rate(50) == 0 ? 1 : myError(7);
    mpu_set_dmp_state(ENABLE) == 0 ? 1 : myError(8);
    run_self_test();
}

void get_sensors(void)
{
	float pitch,roll,yaw;
    short gyro[3], accel[3], sensors;
    unsigned char more;
    long quat[4];
    unsigned long timestamp = 0;
    while(dmp_read_fifo(gyro, accel, quat, &timestamp, &sensors, &more) || more);
    {
/*        float w,x,y,z;
        w = quat[0] / q30;
        x = quat[1] / q30;
        y = quat[2] / q30;
        z = quat[3] / q30;

		pitch = asin(2*w*y - 2*z*x) * 57.3;
		roll = atan2(2*w*x + 2*y*z,1 - 2*x*x - 2*y*y) * 57.3;
		yaw = atan2(2*w*z + 2*x*y,1 - 2*y*y - 2*z*z) * 57.3;
*/
//TODO:        attitude_mixDMPResult(w,x,y,z);
        send_packet(PACKET_TYPE_QUAT,quat);
    }
}
