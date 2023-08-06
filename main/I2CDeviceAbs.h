
#ifndef I2C_DEVICE_ABS_H
#define I2C_DEVICE_ABS_H

#include "DeviceAbs.h"


/* I2C Device  abstract handler*/
class I2CDeviceAbs: public DeviceAbs 
{
    public:
        I2CDeviceAbs(uint8_t addr);
        uint8_t getBaseAddr();
    
    private:
        uint8_t baseI2CAddrOfDevice;
};

#endif