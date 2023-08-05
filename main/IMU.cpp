#include "IMU.h"
#include <M5CoreS3.h>

IMU::IMU()
{
    deviceName            = DEVICE_IMU;
    whereCanConnectDevice = CONNECTION_TYPE_INTERNAL;
    deviceType            = DEVICE_TYPE_I2C;
}

bool IMU::begin()
{
    M5.IMU.Init(); // Init IMU.               
    return true;
}

void IMU::update()
{
    M5.IMU.Update();
}

void IMU::print()
{
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextFont(2);
    M5.Lcd.printf("\nGyroX = %4.2f | Gyro_Y = %4.2f | Gyro_Z = %4.2f\n",
                     M5.IMU.gyro_data.x, M5.IMU.gyro_data.y,
                     M5.IMU.gyro_data.z);
    M5.Lcd.printf("\nAcc_X = %4.2f | Acc_Y = %4.2f | Acc_Z = %4.2f\n",
                     M5.IMU.accel_data.x, M5.IMU.accel_data.y,
                     M5.IMU.accel_data.z);
}