#include <M5CoreS3.h>
#include "PulseOximeterSensor.h"


PulseOximeterSensor::PulseOximeterSensor() :
I2CDeviceAbs(HEART_UNIT_I2C_ADDR)
{
    
}

bool PulseOximeterSensor::begin()
{
    return pox.begin();
}

void PulseOximeterSensor::update()
{
    pox.update();
}

void PulseOximeterSensor::print()
{
    M5.Lcd.setTextFont(4);
    M5.Lcd.setCursor(10, 30, 4);
    M5.Lcd.print("Heart rate:");
    M5.Lcd.print(pox.getHeartRate());
    M5.Lcd.setCursor(10, 60, 4);
    M5.Lcd.print("bpm / SpO2:");
    M5.Lcd.print(pox.getSpO2());
    M5.Lcd.println("%");
}