#include <M5CoreS3.h>
#include "M5Telemetry.h"
#include "PbHubDevice.h"
#include "RGB.h"
#include "Vibration.h"

M5Telemetry M5Tel; // Global external instance of M5Telemetry


/** 
 * @brief Default constructor for M5Telemetry.
 */
M5Telemetry::M5Telemetry()
{
}

/** 
 * @brief Initialize the M5Telemetry system.
 * @details This function initializes M5, enabling Port A, LCD, and Serial Connection.
 */
void M5Telemetry::begin()
{
    // Start M5 initialization with Port A, LCD, and Serial Connection enabled
    M5.begin(true,true,true);

    // Reset all device handlers to NULL
    for (uint8_t i = 0; i < (uint8_t)DEVICE_MAX_DEVICES; i++) 
    {
        pDeviceHandlers[i] = NULL;
    }
}

/** 
 * @brief Scan the PaHub to identify which devices are connected.
 * @details This function maps the connected devices to their corresponding ports on the PaHub.
 */
void M5Telemetry::scanPaHub()
{
    // Scan the PaHub to identify connected devices
    uint8_t port;
    uint8_t deviceId;
    uint8_t i2cAddr;
    uint8_t retVal;
    // Initilizes all port mapping to zero
    for(uint8_t i2cAddr = 0x1; i2cAddr < MAX_I2C_ADDR; i2cAddr++)
    {
        i2cAddrToPortMap[i2cAddr] = PA_HUB_INVALID_PORT; 
    }

    // Mapping all devices which connected to pahub
    for(uint8_t port = static_cast<uint8_t>(PA_HUB_PORT_0); port < static_cast<uint8_t>(PA_HUB_MAX_PORTS); port++)
    {
        i2cAddr = 0x1;
        // Switching to port
        Wire.beginTransmission(PA_HUB_I2C_ADDR);
        Wire.write(1 << port);
        retVal = Wire.endTransmission();
        delay(200);

        if(VALID_I2C_END_TRANSMISSION_VALUE == retVal)
        {
            // Try determine which i2c are responding
            for(; i2cAddr < MAX_I2C_ADDR; i2cAddr++)
            {
                Wire.beginTransmission(i2cAddr);
                if((Wire.endTransmission() == VALID_I2C_END_TRANSMISSION_VALUE) && (PA_HUB_I2C_ADDR != i2cAddr) 
                    && (PA_HUB_I2C_ADDR2 != i2cAddr))
                {
                    // Saving in map the device found in pahub.
                    i2cAddrToPortMap[i2cAddr] = static_cast<PaHubPort_e>(port);
                }
            }
        }
    }
}

/** 
 * @brief Scan for devices connected to the system and initialize them.
 * @param buttonHubAddr Address for the button hub.
 * @param fsrAddr Address for the FSR.
 * @param useRgb flag if use RGB device
 * @details This function scans both internal and external devices, initializing and mapping them.
 */
void M5Telemetry::scan(uint8_t buttonHubAddr, uint8_t fsrAddr, uint8_t vibrationMotorAddress, bool useRgb)
{
    PaHubPort_e        tempPort;
    PaHubDeviceAbs     *pPaHubDeviceHandler;

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

    // Try to connect I2C Devices
    for(uint8_t device = (uint8_t)DEVICE_START_EXTERNAL_PA_HUB; device < (uint8_t)DEVICE_END_EXTERNAL_PA_HUB; device++)
    {
        pPaHubDeviceHandler = static_cast<PaHubDeviceAbs*>(pDeviceHandlers[device]);
        // Retrieve the port which the I2C device is connected
        tempPort = i2cAddrToPortMap[pPaHubDeviceHandler->getBaseAddr()];
        if(tempPort != PA_HUB_INVALID_PORT)
        {
           // USBSerial.printf("i2c addr %02X | PORT %u\n", pPaHubDeviceHandler->getBaseAddr(), tempPort);
            pPaHubDeviceHandler->setPort(tempPort); // Set port attribute in pahub

            /* Try initilize sensor !*/
            if(pPaHubDeviceHandler->begin())
            {
                M5.Lcd.printf("DeviceId %u identified\n", device);
                USBSerial.printf("DeviceId %u identified\n", device);
                pPaHubDeviceHandler->shutdown();
            }
            else
            {
                M5.Lcd.printf("Failed to active DeviceId %u\n", device);
                USBSerial.printf("Failed to active DeviceId %u\n", device);
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

    // Sensors / Devices
    if(PB_HUB_PORT_INVALID_ADDR != fsrAddr)
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

    // Outputs
    if (useRgb)
    {
        // PORT B
        RGBDevice.begin();
    }
    if (PB_HUB_PORT_INVALID_ADDR != vibrationMotorAddress)
    {
        // PB-HUB
        vibrationMotor.begin(vibrationMotorAddress);
    }
    delay(2500);
}


/** 
 * @brief Update the readings for all available devices.
 * @details This function iterates over all connected devices and updates their readings.
 */
void M5Telemetry::update()
{
    for(uint8_t device = (uint8_t)DEVICE_START_ALL_DEVICES; device < (uint8_t)DEVICE_MAX_DEVICES; device++)
    {
        // Determine if device was connected
        if(pDeviceHandlers[device])
        {
            pDeviceHandlers[device]->update();
        }
    }
}

/** 
 * @brief Standalone print function.
 * @param standAloneUpdate Flag to determine if update should be standalone(update only the sensor which is printed to screen).
 * @details Displays sensor data and manages sensor state transitions based on button presses.
 */
void M5Telemetry::standAlonePrint(bool standAloneUpdate)
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
            
            if(standAloneUpdate)
            {
                /* Shutdown the device which was used */
                pDeviceHandlers[state]->shutdown();
            }

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

            if(standAloneUpdate)
            {
                /* Wakeup new device */
                pDeviceHandlers[state]->restart();
            }
        }

        if(standAloneUpdate)
        {
            if(pDeviceHandlers[state])
            {
                pDeviceHandlers[state]->update();
                pDeviceHandlers[state]->print();
            }
        }
        else
        {
            update();
            pDeviceHandlers[state]->print();
        }

        delay(100);
    }
}

/** 
 * @brief Destructor for M5Telemetry.
 * @details Handles cleanup (if necessary) for the M5Telemetry instance.
 */
M5Telemetry::~M5Telemetry()
{
}