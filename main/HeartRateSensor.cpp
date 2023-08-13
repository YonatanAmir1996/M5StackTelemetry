#include <M5CoreS3.h>
#include "HeartRateSensor.h"

#define REPORTING_PERIOD_MS 2000

/**
 * @brief Default constructor. Initializes the heart rate sensor with default I2C address and resets timestamp of last report.
 */
HeartRateSensor::HeartRateSensor() :
PaHubDeviceAbs(HEART_UNIT_I2C_ADDR),
tsLastReport(0)
{
    
}

/**
 * @brief Initializes the HeartRateSensor. Tries to begin the sensor multiple times if the first attempt fails.
 * @return Returns true if the sensor initialization was successful, false otherwise.
 */
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

/**
 * @brief Gathers samples from the PulseOximeter for a specified duration (REPORTING_PERIOD_MS).
 * 
 * The PulseOximeter requires some time to accumulate accurate readings, so samples are taken over
 * a 2-second duration to ensure the readings' reliability and consistency. Making sure to continuously
 * call `pox.update()` helps in accurate tracking and data collection.
 */
void HeartRateSensor::update()
{
    switchPort();
    setFrequency(I2C_BUS_SPEED);
    tsLastReport = millis();
 
    while((millis() - tsLastReport) < REPORTING_PERIOD_MS)
    {
        /* Gather samples*/
        pox.update();
    }
}

/**
 * @brief Shuts down the HeartRateSensor and outputs a shutdown message to USB serial.
 */
void HeartRateSensor::shutdown()
{
    USBSerial.printf("\nShutdown pulse\n");
    switchPort();
    pox.shutdown();
}

/**
 * @brief Restarts the HeartRateSensor.
 * @return Always returns true. Might need additional implementation details for error checking.
 */
bool HeartRateSensor::restart()
{
    setFrequency(I2C_FREQ_400KHZ);
    switchPort(); 
    pox.resume();
    return true;
}

/**
 * @brief Displays the current heart rate and SpO2 readings on the M5 LCD.
 */
void HeartRateSensor::print()
{
    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    M5.Lcd.clear();
    M5.Lcd.setTextFont(4);
    M5.Lcd.setCursor(10, 30, 4);
    M5.Lcd.print("Heart rate:");
    M5.Lcd.print(pox.getHeartRate());
    M5.Lcd.setCursor(10, 60, 4);
    M5.Lcd.print("bpm / SpO2:");
    M5.Lcd.print(pox.getSpO2());
    M5.Lcd.println("%");
}