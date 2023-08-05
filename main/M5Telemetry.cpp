#include <M5CoreS3.h>
#include "M5Telemetry.h"
#include "IMU.h"
#include "PaHub.h"

M5Telemetry M5Tel; // Extern
M5Telemetry::M5Telemetry()
{
    // Enable Port A, LCD and SerialConnection
    M5.begin(true,true,true);
    for (uint8_t i = 0; i < (uint8_t)DEVICE_MAX_DEVICES; i++) 
    {
        pDeviceHandlers[i] = NULL;
    }
}

void M5Telemetry::scan()
{
    PaHubPort_e  tempPort;
    I2CDeviceAbs *pDeviceHandler;

    // Internal Devices handling
    pDeviceHandlers[DEVICE_IMU] = &imuDevice;

    pDeviceHandlers[DEVICE_IMU]->begin();

    //PA_HUB handling (I2C)
    pDeviceHandlers[DEVICE_HEART_UNIT_MAX_30100] = &pulseOximeterDevice;
    PaHubDevice.scan();

    for(uint8_t device = (uint8_t)DEVICE_START_EXTERNAL_PA_HUB; device < (uint8_t)DEVICE_END_EXTERNAL_PA_HUB; device++)
    {
        pDeviceHandler = static_cast<I2CDeviceAbs*>(pDeviceHandlers[device]);

        tempPort = PaHubDevice.i2cAddrToPortMap[pDeviceHandler->getBaseAddr()];
        if(tempPort != PA_HUB_INVALID_PORT)
        {
            // try begin sensor
            PaHubDevice.setPort(tempPort);
            if(pDeviceHandler->begin())
            {
                // Sensor was activated therefore can save the port it is connected
                pDeviceHandler->setPort(tempPort);
            }
            
        }
    }

    // PORT B handling
    
}
M5Telemetry::~M5Telemetry()
{
}