#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

#include <stdint.h>

#define VALID_I2C_END_TRANSMISSION_VALUE 0

/*Defines Addr*/
#define VL3L5CX_TOF_I2C_ADDR             0x29
#define HEART_UNIT_I2C_ADDR              0x57
#define PB_HUB_I2C_ADDR                  0x61
#define AMG8833_I2C_ADDR                 0x69
#define PA_HUB_I2C_ADDR                  0x70
#define MAX_I2C_ADDR                     0x7F

#define RGB_PORT_B_PIN 9


#define PB_HUB_PORT_0_ADDR               0x40
#define PB_HUB_PORT_1_ADDR               0x50
#define PB_HUB_PORT_2_ADDR               0x60
#define PB_HUB_PORT_3_ADDR               0x70
#define PB_HUB_PORT_4_ADDR               0x80
#define PB_HUB_PORT_5_ADDR               0xA0
#define PB_HUB_PORT_INVALID_ADDR         0xFF


/*Enums*/
typedef enum
{
    RUNNING_MODE_STANDALONE,
    RUNNING_MODE_SLAVE
}RunningMode_e;

typedef enum
{
    /* Internal devices mapping */
    DEVICE_START_ALL_DEVICES = 0,
    DEVICE_START_INTERNAL = DEVICE_START_ALL_DEVICES,
    DEVICE_IMU = DEVICE_START_INTERNAL,
    DEVICE_END_INTERNAL,
    /* External devices mapping PAHUB */
    DEVICE_START_EXTERNAL_PA_HUB = DEVICE_END_INTERNAL,
    DEVICE_HEART_UNIT_MAX_30100 = DEVICE_START_EXTERNAL_PA_HUB,
    DEVICE_AMG8833_GRID_EYE,
    DEVICE_VL3L5CX_TOF,
    DEVICE_END_EXTERNAL_PA_HUB,

    /* External device mapping PBHUB */
    DEVICE_START_EXTERNAL_PB_HUB = DEVICE_END_EXTERNAL_PA_HUB,
    DEVICE_FSR402 = DEVICE_START_EXTERNAL_PB_HUB,
    DEVICE_BUTTON,      //Don't init in pDevicesHandlers !
    DEVICE_DC_MOTOR,    //Don't init in pDevicesHandlers !
    DEVICE_END_EXTERNAL_PB_HUB,
    
    /* External device mapping Port B*/
    DEVICE_START_EXTERNAL_PORT_B = DEVICE_END_EXTERNAL_PB_HUB,
    DEVICE_RGB_LED = DEVICE_START_EXTERNAL_PORT_B, //Don't init in pDevicesHandlers !
    DEVICE_END_EXTERNAL_PORT_B,
    DEVICE_MAX_DEVICES = DEVICE_END_EXTERNAL_PORT_B
}DeviceName_e;

typedef enum
{
    DEVICE_TYPE_START = 0,
    DEVICE_TYPE_I2C = DEVICE_TYPE_START,
    DEVICE_TYPE_ANALOG,
    DEVICE_TYPE_PWM,
    DEVICE_TYPE_NEO_PIXEL
}DeviceType_e;

typedef enum
{
    CONNECTION_TYPE_INTERNAL = 0,
    CONNECTION_TYPE_PORT_A,
    CONNECTION_TYPE_PORT_B,
    CONNECTION_TYPE_PA_HUB,
    CONNECTION_TYPE_PB_HUB, 
}ConnectionType_e;


typedef enum
{
    PA_HUB_PORT_0 = 0,
    PA_HUB_PORT_1,
    PA_HUB_PORT_2,
    PA_HUB_PORT_3,
    PA_HUB_PORT_4,
    PA_HUB_PORT_5,
    PA_HUB_MAX_PORTS,
    PA_HUB_INVALID_PORT = 0xFF,
}PaHubPort_e;

typedef enum
{
    PB_HUB_ANALOG_READ = 0x6,
    PB_HUB_PWM_WRITE   = 0x3
}PbHubCommand;

#endif