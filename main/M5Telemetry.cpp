#include <M5CoreS3.h>
#include "M5Telemetry.h"

M5Telemetry M5Tel; // Extern

M5Telemetry::M5Telemetry()
{
}

void M5Telemetry::begin()
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
    PaHubPort_e        tempPort;
    PaHubDeviceAbs     *pPaHubDeviceHandler;


    // Internal Devices handling
    pDeviceHandlers[DEVICE_IMU] = static_cast<DeviceAbs*>(&imuDevice);
    pDeviceHandlers[DEVICE_IMU]->begin();

    //PA_HUB handling (I2C)
    pDeviceHandlers[DEVICE_HEART_UNIT_MAX_30100] = static_cast<DeviceAbs*>(&pulseOximeterDevice);
    pDeviceHandlers[DEVICE_AMG8833_GRID_EYE]     = static_cast<DeviceAbs*>(&gridEyeSensor);
    pDeviceHandlers[DEVICE_VL3L5CX_TOF]          = static_cast<DeviceAbs*>(&tofSensor);

    // Mapping i2c address to the connect port in pahub
    PortAHub.scan(); 

    for(uint8_t device = (uint8_t)DEVICE_START_EXTERNAL_PA_HUB; device < (uint8_t)DEVICE_END_EXTERNAL_PA_HUB; device++)
    {
        pPaHubDeviceHandler = static_cast<PaHubDeviceAbs*>(pDeviceHandlers[device]);

        tempPort = PortAHub.i2cAddrToPortMap[pPaHubDeviceHandler->getBaseAddr()];
        USBSerial.printf("i2c addr %02X | PORT %u", pPaHubDeviceHandler->getBaseAddr(), tempPort);
        if(tempPort != PA_HUB_INVALID_PORT)
        {
            // try begin sensor
            pPaHubDeviceHandler->setPort(tempPort);
            pPaHubDeviceHandler->switchPort();
            if(pPaHubDeviceHandler->begin())
            {
                // Sensor was activated therefore can save the port it is connected
            }
            else
            {
                pPaHubDeviceHandler[device] = NULL; // Remove from available devices
            }
        }
    }

    // PORT B handling
    
}


// Update all available devices values
void M5Telemetry::update()
{
    for(uint8_t device = (uint8_t)DEVICE_START_ALL_DEVICES; device < (uint8_t)DEVICE_MAX_DEVICES; device++)
    {
        if(pDeviceHandlers[device])
        {
            // Update sensor data
            pDeviceHandlers[device]->update();
        }
    }
}

void M5Telemetry::standAlonePrint()
{
    for(uint8_t device = (uint8_t)DEVICE_START_ALL_DEVICES; device < (uint8_t)DEVICE_MAX_DEVICES; device++)
    {
        if(pDeviceHandlers[device])
        {
            // Update sensor data
            pDeviceHandlers[device]->print();
        }
        delay(500);
    }

}

M5Telemetry::~M5Telemetry()
{
}