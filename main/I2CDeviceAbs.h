
#ifndef I2C_DEVICE_ABS_H
#define I2C_DEVICE_ABS_H

#include "DeviceAbs.h"


/**
 * @brief Abstract handler for I2C-based devices.
 * 
 * This class provides a foundational structure for all I2C devices. It extends the basic device
 * functionalities provided by the `DeviceAbs` class and introduces I2C specific attributes 
 * and functionalities.
 */
class I2CDeviceAbs: public DeviceAbs 
{
    public:
        I2CDeviceAbs(uint8_t addr);
        uint8_t getBaseAddr();
    
    private:
        uint8_t baseI2CAddrOfDevice;
};

#endif