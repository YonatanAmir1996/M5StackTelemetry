#include "PaHubDeviceAbs.h"
#include <M5CoreS3.h>


/**
 * @brief Constructor for the PaHubDeviceAbs class.
 * @param addr I2C address of the device.
 */
PaHubDeviceAbs::PaHubDeviceAbs(uint8_t addr) : 
connectedPort(PA_HUB_INVALID_PORT),
I2CDeviceAbs(addr)
{

}

/**
 * @brief Destructor for the PaHubDeviceAbs class.
 */
PaHubDeviceAbs::~PaHubDeviceAbs() {}



/**
 * @brief Set the port to which the device is connected.
 * @param port The port to be set.
 */
void PaHubDeviceAbs::setPort(PaHubPort_e port)
{
    connectedPort = port;
}

/**
 * @brief Get the port to which the device is connected.
 * @return Returns the connected port.
 */
PaHubPort_e PaHubDeviceAbs::getPort()
{
    return connectedPort;
}

/**
 * @brief Switch to the specified port for transmission.
 * 
 * The method sets up a communication channel to the specified port on the PaHub.
 */
void PaHubDeviceAbs::switchPort()
{
    setFrequency(I2C_FREQ_100KHZ);
    /* Method selects a port to transimition info*/
    Wire.beginTransmission(PA_HUB_I2C_ADDR);
    Wire.write(1 << (uint8_t)connectedPort);
    Wire.endTransmission(); 
}