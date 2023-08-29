#include <M5CoreS3.h>
#include "HeartRateSensor.h"

#define REPORTING_PERIOD_MS 2000

/**
 * @brief Default constructor. Initializes the heart rate sensor with default I2C address and resets timestamp of last report.
 */
HeartRateSensor::HeartRateSensor() :
PaHubDeviceAbs(HEART_UNIT_I2C_ADDR),
tsLastReport(0),
heartRate(0),
spo2(0)
{
    
}

/**
 * @brief Initializes the HeartRateSensor. Tries to begin the sensor multiple times if the first attempt fails.
 * @return Returns true if the sensor initialization was successful, false otherwise.
 */
bool HeartRateSensor::begin()
{
    uint8_t count = 0;

    setFrequency(I2C_FREQ_400KHZ);
    switchPort();

    return pox.begin();
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
    setFrequency(I2C_FREQ_400KHZ);
    switchPort();
    tsLastReport = millis();
 
    while((millis() - tsLastReport) < REPORTING_PERIOD_MS)
    {
        /* Gather samples*/
        pox.update();
    }

    //heartRate = pox.getHeartRate();
    //spo2      = pox.getSpO2();
}

/**
 * @brief Shuts down the HeartRateSensor and outputs a shutdown message to USB serial.
 */
void HeartRateSensor::shutdown()
{
    setFrequency(I2C_FREQ_400KHZ);
    switchPort();
    pox.shutdown();
}

/**
 * @brief Restarts the HeartRateSensor.
 * @return Always returns true. Might need additional implementation details for error checking.
 */
bool HeartRateSensor::restart()
{
    switchPort(); 
    setFrequency(I2C_FREQ_400KHZ);
    pox.resume();
    return true;
}

/**
 * @brief Displays the current heart rate and SpO2 readings on the M5 LCD.
 */
void HeartRateSensor::print()
{
    setFrequency(I2C_FREQ_400KHZ);
    switchPort(); 
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

uint32_t HeartRateSensor::writeIntoTxBuffer(uint32_t offset)
{
    uint32_t  deviceName = DEVICE_HEART_UNIT_MAX_30100;
    uint32_t  deviceNumOfBytesToRead;
    float     heartRate;
    uint8_t   spO2;

    update();
    deviceNumOfBytesToRead = sizeof(deviceName) + sizeof(heartRate) + sizeof(spO2);
    heartRate = pox.getHeartRate();
    spO2      = pox.getSpO2();

    memcpy(TxBuffer + offset, &deviceNumOfBytesToRead, sizeof(deviceNumOfBytesToRead));
    offset += sizeof(deviceNumOfBytesToRead);
    memcpy(TxBuffer + offset, &deviceName, sizeof(deviceName));
    offset += sizeof(deviceName);
    memcpy(TxBuffer + offset, &heartRate, sizeof(heartRate));
    offset += sizeof(heartRate);
    memcpy(TxBuffer + sizeof(heartRate) + offset, &spO2, sizeof(spO2));
    offset += sizeof(spO2);
    return deviceNumOfBytesToRead + sizeof(deviceNumOfBytesToRead);
}