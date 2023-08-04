
#define PB_HUB_I2C_ADDR 0x61;
#define PA_HUB_I2C_ADDR 0x70;
#define HEART_UNIT_I2C_ADDR 0x57;
#define VL3L

#define PB_HUB_PORT_0_ADDR 0x40;
#define PB_HUB_PORT_1_ADDR 0x50;
#define PB_HUB_PORT_2_ADDR 0x60;
#define PB_HUB_PORT_3_ADDR 0x70;
#define PB_HUB_PORT_4_ADDR 0x80;
#define PB_HUB_PORT_5_ADDR 0xA0;

typedef enum
{
    STANDALONE = 0,
    SLAVE
}RunningMode_e;

typedef enum
{
    IMU = 0,
    HEART_UNIT_MAX_30100,
    AMG8833_GRID_EYE,
    VL3L5CX_TOF,
    FSR402,
    RGB_LED,
    DC_MOTOR
}AvailableDevices_e;

typedef enum
{
    PA_HUB_PORT_0 = 0,
    PA_HUB_PORT_1,
    PA_HUB_PORT_2,
    PA_HUB_PORT_3,
    PA_HUB_PORT_4,
    PA_HUB_PORT_5,
    PA_HUB_MAX_PORTS
}PaHubPorts_e;

typedef enum
{
    PB_HUB_PORT = 0,
}PbhubPorts_e;