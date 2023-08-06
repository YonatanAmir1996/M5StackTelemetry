#include "I2CDeviceAbs.h"
#include <M5CoreS3.h>

I2CDeviceAbs::I2CDeviceAbs(uint8_t addr) :
baseI2CAddrOfDevice(addr)
{
}

uint8_t I2CDeviceAbs::getBaseAddr()
{
    // Returns I2C base address
    return baseI2CAddrOfDevice;
}