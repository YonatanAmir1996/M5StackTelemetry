#include <M5CoreS3.h>
#include "DeviceAbs.h"


 /**
 * @brief Virtual method for initializing the device.
 * @return true if the device is initialized successfully, false otherwise.
 */
bool DeviceAbs::begin()
{
    return true;
}

/**
 * @brief Initializes the device with a specific address.
 * @param addr The address to initialize the device with.
 * @return true since the operation is always successful.
 */
bool DeviceAbs::begin(uint8_t addr)
{
    return true;
}

/**
 * @brief Restarts the device.
 * @return true since the operation is always successful.
 */
bool DeviceAbs::restart() 
{
    return true;
}

/**
 * @brief Default update method for the device.
 * @details This is a placeholder method that derived classes should override.
 */
void DeviceAbs::update() {}

/**
 * @brief Default print method for the device.
 * @details This is a placeholder method that derived classes should override.
 */
void DeviceAbs::print() {}

/**
 * @brief Shuts down the device.
 * @details This is a placeholder method that derived classes should override.
 */
void DeviceAbs::shutdown()  {}

/**
 * @brief Sets the I2C communication frequency.
 * @details If the current frequency doesn't match the provided frequency, it sets the new frequency.
 * @param freq The desired frequency.
 */
void DeviceAbs::setFrequency(uint32_t freq)
{
    if(Wire.getClock() != freq)
    {
        Wire.setClock(freq);
    }
}