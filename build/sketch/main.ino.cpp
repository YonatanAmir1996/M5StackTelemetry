#include <Arduino.h>
#line 1 "D:\\M5StackTelemetry\\source\\main\\main.ino"
#include <M5CoreS3.h>

/* After M5CoreS3 is started or reset the program in the setUp()
function will be run, and this part will only be run once.
*/
void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3. 
    M5.Lcd.setTextSize(2);        // Set text size. 
    M5.Lcd.setCursor(0, 0);       // Set the cursor.
    delay(200);                   // Delay 200ms.  
    M5.IMU.Init();                // Init IMU. 
}

void loop() {
  M5.IMU.Update();  // Update data from IMU. 更新IMU数据
    M5.Lcd.setCursor(30, 30);
    M5.Lcd.printf("Made by Yonatan Amir\n");
    // gyro scope output related.
    M5.Lcd.setCursor(30, 60);
    M5.Lcd.printf("gyroX,  gyroY, gyroZ");  // Screen printingformatted string.
    M5.Lcd.setCursor(30, 90);
    M5.Lcd.fillRect(30, 90, 320, 20, BLACK);
    M5.Lcd.printf("%4.2f\t   %4.2f\t   %4.2f", M5.IMU.gyro_data.x,
                  M5.IMU.gyro_data.y, M5.IMU.gyro_data.z);

    // Accelerometer output is related
    M5.Lcd.setCursor(30, 120);
    M5.Lcd.printf("accX,   accY,  accZ");
    M5.Lcd.setCursor(30, 150);
    M5.Lcd.fillRect(30, 150, 320, 20, BLACK);
    M5.Lcd.printf("%4.2f\t   %4.2f\t   %4.2f", M5.IMU.accel_data.x,
                  M5.IMU.accel_data.y, M5.IMU.accel_data.z);

    USBSerial.printf("\nGyro_X = %4.2f\t Gyro_Y = %4.2f\t Gyro_Z = %4.2f\n\n",
                     M5.IMU.gyro_data.x, M5.IMU.gyro_data.y,
                     M5.IMU.gyro_data.z);
    USBSerial.printf("\nAcc_X = %4.2f\t Acc_Y = %4.2f\t Acc_Z = %4.2f\n",
                     M5.IMU.accel_data.x, M5.IMU.accel_data.y,
                     M5.IMU.accel_data.z);

    delay(10);
}
