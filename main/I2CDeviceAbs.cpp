#include "I2CDeviceAbs.h"
#include <M5CoreS3.h>


 /**
 * @brief Constructor that initializes the I2C device with its base I2C address.
 * @param addr The I2C base address of the device.
 */
I2CDeviceAbs::I2CDeviceAbs(uint8_t addr) :
baseI2CAddrOfDevice(addr)
{
}

/**
 * @brief Fetches the base I2C address of the device.
 * @return Returns the base I2C address.
*/
uint8_t I2CDeviceAbs::getBaseAddr()
{
    // Returns I2C base address
    return baseI2CAddrOfDevice;
}