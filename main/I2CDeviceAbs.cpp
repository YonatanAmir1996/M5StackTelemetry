#include "I2CDeviceAbs.h"


I2CDeviceAbs::I2CDeviceAbs(uint8_t addr) :
baseI2CAddrOfDevice(addr),
port(PA_HUB_INVALID_PORT)
{
}

uint8_t I2CDeviceAbs::getBaseAddr()
{
    // Returns I2C base address
    return baseI2CAddrOfDevice;
}

uint8_t I2CDeviceAbs::setPort(PaHubPort_e port)
{
    // Set's port number the device connected
    port = PA_HUB_INVALID_PORT;
}