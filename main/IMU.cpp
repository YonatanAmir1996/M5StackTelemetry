#include "IMU.h"
#include <M5CoreS3.h>

/**
 * @brief IMU constructor.
 * 
 * Initializes the IMU device attributes.
 */
IMU::IMU()
{
}

/**
 * @brief Initializes the IMU device.
 * 
 * @return Returns true after successful initialization.
 */
bool IMU::begin()
{
    M5.IMU.Init(); // Init IMU.               
    return true;
}

/**
 * @brief Updates the IMU's data readings.
 */
void IMU::update()
{
    M5.IMU.Update();
}

/**
 * @brief Prints the IMU data (gyroscope and accelerometer readings) on the M5's LCD screen.
 */
void IMU::print()
{
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