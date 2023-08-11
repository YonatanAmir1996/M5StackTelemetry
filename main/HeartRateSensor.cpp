#include <M5CoreS3.h>
#include "HeartRateSensor.h"

#define REPORTING_PERIOD_MS 2000

HeartRateSensor::HeartRateSensor() :
PaHubDeviceAbs(HEART_UNIT_I2C_ADDR),
tsLastReport(0)
{
    
}

bool HeartRateSensor::begin()
{
    uint8_t count = 0;
    bool    ready = pox.begin();

    if (!ready && count < NUMBER_OF_BEGIN_TRIES) 
    {
        count++;
        delay(100);
        ready = pox.begin();
    }
    return ready;
}

void HeartRateSensor::update()
{
    pox.update();
}

void HeartRateSensor::shutdown()
{
    USBSerial.printf("\nShutdown pulse\n");
    switchPort();
    setFrequency();
    pox.shutdown();
}
void HeartRateSensor::setFrequency()
{
    if(Wire.getClock() != I2C_BUS_SPEED)
    {
        Wire.setClock(I2C_BUS_SPEED);
        delay(100);
    }
}
bool HeartRateSensor::restart()
{
    switchPort();
    setFrequency();
    pox.resume();
    return true;
}

void HeartRateSensor::print()
{
    switchPort();
    setFrequency();
    tsLastReport = millis();

    /* Gather samples*/
    while((millis() - tsLastReport) < REPORTING_PERIOD_MS)
    {
    // Make sure to call update as fast as possible
        pox.update();
    }
    USBSerial.printf("\ninside here5\n");

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextFont(4);
    M5.Lcd.setCursor(10, 30, 4);
    M5.Lcd.print("Heart rate:");
    M5.Lcd.print(pox.getHeartRate());
    M5.Lcd.setCursor(10, 60, 4);
    M5.Lcd.print("bpm / SpO2:");
    M5.Lcd.print(pox.getSpO2());
    M5.Lcd.println("%");
}