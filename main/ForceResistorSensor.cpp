#include "ForceResistorSensor.h"
#include "PbHubDevice.h"

/**
 * @brief Default constructor. Initializes the hub address and FSR value to zero.
 */
ForceResistorSensor::ForceResistorSensor() :
hubAddr(0),
fsrValue(0)
{
}

/**
 * @brief Initializes the ForceResistorSensor with a specific address.
 * @param addr Address to initialize the sensor with.
 * @return Always returns true. Might need additional implementation details for error checking.
 */
bool ForceResistorSensor::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}

/**
 * @brief Updates the fsrValue by reading the current value from PbHub.
 */
void ForceResistorSensor::update()
{
    fsrValue = PbHub.readAnalogVal(hubAddr);
}

/**
 * @brief Displays the current FSR value on the M5 LCD.
 */
void ForceResistorSensor::print()
{
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.print("FSR Value: ");
    M5.Lcd.println(fsrValue);
    delay(100);
}