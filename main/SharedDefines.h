#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

#include <stdint.h>

// Represents a successful I2C end transmission
#define VALID_I2C_END_TRANSMISSION_VALUE 0

// I2C Address Definitions
#define VL3L5CX_TOF_I2C_ADDR             0x29  // I2C address for VL3L5CX TOF sensor
#define HEART_UNIT_I2C_ADDR              0x57  // I2C address for heart rate unit
#define PB_HUB_I2C_ADDR                  0x61  // I2C address for PB hub
#define AMG8833_I2C_ADDR                 0x69  // I2C address for AMG8833 sensor
#define PA_HUB_I2C_ADDR                  0x70  // I2C address for PA hub
#define PA_HUB_I2C_ADDR2                 0x75  // I2C address for PA hub
#define MAX_I2C_ADDR                     0x7F  // Max I2C address

 // Pin for the RGB on port B
#define RGB_PORT_B_PIN 9

// register address Definitions for PB Hub Ports
#define PB_HUB_PORT_0_ADDR               0x40
#define PB_HUB_PORT_1_ADDR               0x50
#define PB_HUB_PORT_2_ADDR               0x60
#define PB_HUB_PORT_3_ADDR               0x70
#define PB_HUB_PORT_4_ADDR               0x80
#define PB_HUB_PORT_5_ADDR               0xA0
#define PB_HUB_PORT_INVALID_ADDR         0xFF // Invalid address for PB hub port


/*Enums*/
// Enum to define the mode in which the system is running
typedef enum
{
    RUNNING_MODE_START = 0,
        // System operates as a slave to another device/system
    RUNNING_MODE_SLAVE_START = RUNNING_MODE_START,
    RUNNING_MODE_SERIAL = RUNNING_MODE_SLAVE_START,
    RUNNING_MODE_WIFI,
    RUNNING_MODE_SLAVE_END = RUNNING_MODE_WIFI,
    // System operates independently
    RUNNING_MODE_STANDALONE,
    RUNNING_MODE_END, 
} RunningMode_e;

// Enum to identify internal and external devices. Please set only devices which are used as sensors !
typedef enum
{
    DEVICE_START_ALL_DEVICES = 0,
    DEVICE_START_INTERNAL = DEVICE_START_ALL_DEVICES, // Starting point for internal devices
    DEVICE_IMU = DEVICE_START_INTERNAL,  // Internal IMU device
    DEVICE_END_INTERNAL,                 // Endpoint for internal devices
    DEVICE_START_EXTERNAL_PA_HUB = DEVICE_END_INTERNAL,  // Starting point for external devices connected to PA HUB
    DEVICE_HEART_UNIT_MAX_30100 = DEVICE_START_EXTERNAL_PA_HUB, // External heart unit device
    DEVICE_AMG8833_GRID_EYE,  // External AMG8833 Grid Eye sensor
    DEVICE_VL3L5CX_TOF,       // External VL3L5CX TOF sensor
    DEVICE_END_EXTERNAL_PA_HUB,          // Endpoint for external devices on PA HUB

    DEVICE_START_EXTERNAL_PB_HUB = DEVICE_END_EXTERNAL_PA_HUB,  // Starting point for devices on PB HUB
    DEVICE_FSR402 = DEVICE_START_EXTERNAL_PB_HUB,  // External Force Sensitive Resistor sensor
    DEVICE_FSR402_1,
    DEVICE_END_EXTERNAL_PB_HUB,          // Endpoint for external devices on PB HUB

    DEVICE_START_EXTERNAL_PORT_B = DEVICE_END_EXTERNAL_PB_HUB,  // Starting point for devices on Port B
    DEVICE_END_EXTERNAL_PORT_B = DEVICE_START_EXTERNAL_PORT_B,  // Endpoint for external devices on Port B
    DEVICE_MAX_DEVICES = DEVICE_END_EXTERNAL_PORT_B  // Maximum number of supported devices
} DeviceName_e;


// Enum to specify the ports available on PA HUB
typedef enum
{
    PA_HUB_PORT_0 = 0, // Port 0 on PA HUB
    PA_HUB_PORT_1,     // Port 1 on PA HUB
    PA_HUB_PORT_2,     // Port 2 on PA HUB
    PA_HUB_PORT_3,     // Port 3 on PA HUB
    PA_HUB_PORT_4,     // Port 4 on PA HUB
    PA_HUB_PORT_5,     // Port 5 on PA HUB
    PA_HUB_MAX_PORTS,  // Maximum number of ports on PA HUB
    PA_HUB_INVALID_PORT = 0xFF,  // Invalid port on PA HUB
} PaHubPort_e;

// Enum to identify commands for PB HUB
typedef enum
{
    PB_HUB_ANALOG_READ = 0x6,  // Command to read analog data from PB HUB
    PB_HUB_PWM_WRITE   = 0x3   // Command to write PWM data to PB HUB
} PbHubCommand_e;


typedef enum
{
    COMMAND_START = 0,
    COMMAND_RESCAN_SENSORS = COMMAND_START,
    COMMAND_RUN_SENSORS,
    COMMAND_SET_RGB,
    COMMAND_SET_MOTOR,
    COMMAND_SET_SPEAKER,
    COMMAND_MAX_COMMANDS,
    COMMAND_INVALID = 0xFF
} Commands_e;

typedef struct
{
  const char *ssid; 
  const char *password;
  const char *serverAddress;
  uint16_t    serverPort;
} WifiStruct;



#endif