#include <M5CoreS3.h>
#include "PulseOximeterSensor.h"


PulseOximeterSensor::PulseOximeterSensor() :
PaHubDeviceAbs(HEART_UNIT_I2C_ADDR)
{
    
}

bool PulseOximeterSensor::begin()
{
    return pox.begin();
}

void PulseOximeterSensor::update()
{
    switchPort();
    pox.update();
}

void PulseOximeterSensor::print()
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(2);
    M5.Lcd.print("PulseOximeterSensor");
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.print("Heart rate:");
    M5.Lcd.print(pox.getHeartRate());
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.print("bpm / SpO2:");
    M5.Lcd.print(pox.getSpO2());
    M5.Lcd.println("%");
}