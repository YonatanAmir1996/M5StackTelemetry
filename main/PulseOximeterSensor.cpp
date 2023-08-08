#include <M5CoreS3.h>
#include "PulseOximeterSensor.h"

#define REPORTING_PERIOD_MS 100

PulseOximeterSensor::PulseOximeterSensor() :
PaHubDeviceAbs(HEART_UNIT_I2C_ADDR),
tsLastReport(0)
{
    
}

bool PulseOximeterSensor::begin()
{
    return pox.begin();
}

void PulseOximeterSensor::update()
{
    
}

void PulseOximeterSensor::print()
{
    // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        M5.Lcd.fillScreen(BLACK);
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