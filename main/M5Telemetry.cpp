#include <M5CoreS3.h>
#include "M5Telemetry.h"
#include "PbHubDevice.h"

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

void M5Telemetry::scanPaHub()
{
    uint8_t port;
    uint8_t deviceId;
    uint8_t i2cAddr;

    /* Initilizes all port mapping to zero*/
    for(uint8_t i2cAddr = 0x1; i2cAddr < PA_HUB_MAX_PORTS; i2cAddr++)
    {
        i2cAddrToPortMap[i2cAddr] = PA_HUB_INVALID_PORT; // NULL I2C ADDRESS
    }

    /*Mapping all devices which connected to pahub*/
    for(uint8_t port = static_cast<uint8_t>(PA_HUB_PORT_0); port < static_cast<uint8_t>(PA_HUB_MAX_PORTS); port++)
    {
        i2cAddr = 0x1;
        // Switching to relevent port
        Wire.beginTransmission(PA_HUB_I2C_ADDR);
        Wire.write(1 << port);
        Wire.endTransmission(); 

        /* Finds which i2c address is connected */
        for(; i2cAddr < MAX_I2C_ADDR; i2cAddr++)
        {
            Wire.beginTransmission(i2cAddr);
            if((Wire.endTransmission() == VALID_I2C_END_TRANSMISSION_VALUE) && (PA_HUB_I2C_ADDR != i2cAddr))
            {
                // Saving in map the device found in pahub.
                i2cAddrToPortMap[i2cAddr] = static_cast<PaHubPort_e>(port);
            }
            delay(1);
        }
    }
}

void M5Telemetry::scan(uint8_t buttonHubAddr, uint8_t fsrAddr)
{
    PaHubPort_e        tempPort;
    PaHubDeviceAbs     *pPaHubDeviceHandler;
    bool                deviceExists;

    M5.Lcd.printf("Scanning devices...\n");

    // Internal Devices handling
    pDeviceHandlers[DEVICE_IMU] = static_cast<DeviceAbs*>(&imuDevice);
    pDeviceHandlers[DEVICE_IMU]->begin();

    //PA_HUB handling (I2C)
    pDeviceHandlers[DEVICE_HEART_UNIT_MAX_30100] = static_cast<DeviceAbs*>(&pulseOximeterDevice);
    pDeviceHandlers[DEVICE_AMG8833_GRID_EYE]     = static_cast<DeviceAbs*>(&gridEyeSensor);
    pDeviceHandlers[DEVICE_VL3L5CX_TOF]          = static_cast<DeviceAbs*>(&tofSensor);

    // Mapping i2c address to the connect port in pahub
    M5.Lcd.printf("Scanning PaHub Devices...\n");
    scanPaHub(); 

    for(uint8_t device = (uint8_t)DEVICE_START_EXTERNAL_PA_HUB; device < (uint8_t)DEVICE_END_EXTERNAL_PA_HUB; device++)
    {
        pPaHubDeviceHandler = static_cast<PaHubDeviceAbs*>(pDeviceHandlers[device]);
        //deviceExists        = false;
        tempPort = i2cAddrToPortMap[pPaHubDeviceHandler->getBaseAddr()];
        USBSerial.printf("i2c addr %02X | PORT %u", pPaHubDeviceHandler->getBaseAddr(), tempPort);
        if(tempPort != PA_HUB_INVALID_PORT)
        {
            // Sensor was activated therefore can save the port it is connected
            pPaHubDeviceHandler->setPort(tempPort);
            pPaHubDeviceHandler->switchPort();
            if(pPaHubDeviceHandler->begin())
            {
                pPaHubDeviceHandler->shutdown();
            }
            else
            {
                pDeviceHandlers[device] = NULL; // Remove from available devices
            }
        }
        else
        {
            pDeviceHandlers[device] = NULL; // Remove from available devices
        }
    }

    // PB-HUB
    M5.Lcd.printf("Scanning PbHub Decvices...\n");
    PbHub.setPort(i2cAddrToPortMap[PbHub.getBaseAddr()]);

    pDeviceHandlers[DEVICE_FSR402] = static_cast<DeviceAbs*>(&fsr);

    // Sensors
    if(fsrAddr != PB_HUB_PORT_INVALID_ADDR)
    {
        fsr.begin(fsrAddr);
    }

    // internal devices (interrupt / lcd handling etc...)
    if(buttonHubAddr == PB_HUB_PORT_INVALID_ADDR)   
    {
        M5.Lcd.printf("Button must be set!\n Reset Device.");
        while(1) {};
    }
    button.begin(buttonHubAddr); 


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
    /* Print to screen and update values for each module*/
    uint8_t state = (DeviceName_e)DEVICE_IMU;

    //Find first activated sensor
    while(!pDeviceHandlers[state])
    {
        state += 1;
    }
    while(1)
    {
        if(button.IfButtonPressed())
        {
            /* Shutdown sensor prevent I2C issues */
            static_cast<HeartRateSensor*>(pDeviceHandlers[state])->shutdown();

            state += 1;
            while(!pDeviceHandlers[state])
            {
                state += 1;
                if(state == DEVICE_MAX_DEVICES)
                {
                    state = DEVICE_IMU;
                }
            }
            if(state == DEVICE_MAX_DEVICES)
            {
                state = DEVICE_IMU;
            }
            pDeviceHandlers[state]->restart();
        }

        if(pDeviceHandlers[state])
        {
            pDeviceHandlers[state]->print();
        }
    }

}

M5Telemetry::~M5Telemetry()
{
}