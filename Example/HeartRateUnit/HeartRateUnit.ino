/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5Core sample source code
*                          配套  M5Core 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/gray
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/gray
*
* Describe: Heart Rate.  心率
* Date: 2021/8/16
*******************************************************************************
  Please connect to Port A, HEART Unit obtains the original value of the heart
rate detection and displays it on the screen. The user can also use the Arduino
IDE Serial Plotter to view the line graph output. 请连接端口A,HEART
Unit获取心率检测的原始值并显示在屏幕上。用户还可以使用Arduino IDE Serial
Plotter查看线图输出。
*/

#include <M5CoreS3.h>

#include "MAX30100_PulseOximeter.h"


#define REPORTING_PERIOD_MS 100

uint32_t tsLastReport = 0;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    USBSerial.println("Beat!");
}
// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;

void setup() {
    M5.begin(true, true, true);        // Init M5Stack.  初始化M5Stack
    Serial.print("Initializing MAX30100..");

    while (!pox.begin()) {  // Initialize the sensor.  初始化传感器
        M5.Lcd.setTextFont(4);
        M5.Lcd.setCursor(50, 100, 4);
        M5.Lcd.println("Sensor not found");
        delay(1000);
    }
    M5.Lcd.fillScreen(BLACK);
    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
     // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        M5.Lcd.setTextFont(4);
        M5.Lcd.setCursor(10, 30, 4);
        M5.Lcd.print("Heart rate:");
        M5.Lcd.print(pox.getHeartRate());
        M5.Lcd.setCursor(10, 60, 4);
        M5.Lcd.print("bpm / SpO2:");
        M5.Lcd.print(pox.getSpO2());
        M5.Lcd.println("%");

        tsLastReport = millis();
    }
}