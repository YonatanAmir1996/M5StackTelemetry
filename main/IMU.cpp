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
    update();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(2);
    M5.Lcd.print("IMU");
    M5.Lcd.setCursor(0, 30);
    M5.Lcd.printf("GyroX = %4.0f | Gyro_Y = %4.0f | Gyro_Z = %4.0f\n",
                     M5.IMU.gyro_data.x, M5.IMU.gyro_data.y,
                     M5.IMU.gyro_data.z);
    M5.Lcd.printf("\nAcc_X = %4.0f | Acc_Y = %4.0f | Acc_Z = %4.0f\n",
                     M5.IMU.accel_data.x, M5.IMU.accel_data.y,
                     M5.IMU.accel_data.z);
    delay(100);
}