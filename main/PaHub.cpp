#include <M5CoreS3.h>
#include "PaHub.h"


PaHub PaHubDevice;

PaHub::PaHub() :
I2CDeviceAbs(PA_HUB_I2C_ADDR)
{
    uint8_t port;

    /* Initilizes all port mapping to zero*/
    for(uint8_t i2cAddr = 0x1; i2cAddr < PA_HUB_MAX_PORTS; i2cAddr++)
    {
        i2cAddrToPortMap[i2cAddr] = PA_HUB_INVALID_PORT; // NULL I2C ADDRESS
    }
}

void PaHub::portSelect(PaHubPort_e port)
{
    /* Method selects a port to transimition info*/
    Wire.beginTransmission(getBaseAddr());
    Wire.write(1 << (uint8_t)port);
    Wire.endTransmission(); 
}

void PaHub::scan()
{
    uint8_t deviceId;
    uint8_t i2cAddr;

    for(uint8_t port = static_cast<uint8_t>(PA_HUB_PORT_0); port < static_cast<uint8_t>(PA_HUB_MAX_PORTS); port++)
    {
        i2cAddr = 0x1;
        // Switching to relevent port
        portSelect(static_cast<PaHubPort_e>(port));
        for(; i2cAddr < MAX_I2C_ADDR; i2cAddr++)
        {
            Wire.beginTransmission(i2cAddr);
            if((Wire.endTransmission() == VALID_I2C_END_TRANSMISSION_VALUE) && (getBaseAddr() != i2cAddr))
            {
                // Saving in map the device found in pahub.
                i2cAddrToPortMap[i2cAddr] = static_cast<PaHubPort_e>(port);
            }
        }
    }
}