#include "PaHubDeviceAbs.h"
#include <M5CoreS3.h>

PaHubDeviceAbs::PaHubDeviceAbs(uint8_t addr) : 
connectedPort(PA_HUB_INVALID_PORT),
I2CDeviceAbs(addr)
{

}

PaHubDeviceAbs::~PaHubDeviceAbs() {}


/*set the port which the device is connected to*/
void PaHubDeviceAbs::setPort(PaHubPort_e port)
{
    connectedPort = port;
}

PaHubPort_e PaHubDeviceAbs::getPort()
{
    return connectedPort;
}

void PaHubDeviceAbs::switchPort()
{
    /* Method selects a port to transimition info*/
    Wire.beginTransmission(PA_HUB_I2C_ADDR);
    Wire.write(1 << (uint8_t)connectedPort);
    Wire.endTransmission(); 
}