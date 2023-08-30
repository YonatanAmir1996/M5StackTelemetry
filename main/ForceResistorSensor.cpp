#include "ForceResistorSensor.h"
#include "PbHubDevice.h"
#include "RGB.h"
#include "Vibration.h"

#define FSR_THRESHOLD 1000

/**
 * @brief Default constructor. Initializes the hub address and FSR value to zero.
 */
ForceResistorSensor::ForceResistorSensor() :
hubAddr(PB_HUB_PORT_INVALID_ADDR),
fsrValue(0),
outputWasSet(false)
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
    /*
    if(!outputWasSet && (fsrValue > FSR_THRESHOLD))
    {
        RGBDevice.SetRGB(0, 0, 100, 0);
        RGBDevice.SetRGB(1, 0, 100, 0);
        RGBDevice.SetRGB(2, 0, 100, 0);
        vibrationMotor.setMotor(50);
        outputWasSet = true;
    }
    else if(outputWasSet && (fsrValue < FSR_THRESHOLD))
    {
        RGBDevice.SetRGB(0, 0, 0, 0);
        RGBDevice.SetRGB(1, 0, 0, 0);
        RGBDevice.SetRGB(2, 0, 0, 0);
        vibrationMotor.setMotor(0);
        outputWasSet = false;
    }
    */
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

uint32_t ForceResistorSensor::writeIntoTxBuffer(uint32_t offset)
{
    uint32_t deviceName             = DEVICE_FSR402;
    uint32_t deviceNumOfBytesToRead = sizeof(deviceName) + sizeof(fsrValue);

    update();

    memcpy(TxBuffer + offset, &deviceNumOfBytesToRead, sizeof(deviceNumOfBytesToRead));
    offset += sizeof(deviceNumOfBytesToRead);
    memcpy(TxBuffer + offset, &deviceName, sizeof(deviceName));
    offset += sizeof(deviceName);
    memcpy(TxBuffer + offset, &fsrValue, sizeof(fsrValue));

    return deviceNumOfBytesToRead + sizeof(deviceNumOfBytesToRead);
}