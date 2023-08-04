
typedef enum {
    PORT_A = 0, // I2C
    PORT_B = 1, // PWM/ANALOG/GPIO...
    PORT_C = 2, // UART
}M5TelemetryPorts_e;

typedef enum {
    VL53L5CX_TOF_ADDR           = 0x52,
    HEART_UNIT_ADDR             = 0x57,
    PORT_B_HUB_ADDR             = 0x61,
    AMG8833_THERMAL_SENSOR_ADDR = 0x69,
    PORT_A_HUB_ADDR             = 0x70,
}I2CDevicesAddr_e;

typedef enum {
 PORT_B_HUB_0 = 0x40,
 PORT_B_HUB_1 = 0x50,
 PORT_B_HUB_2 = 0x60,
 PORT_B_HUB_3 = 0x70,
 PORT_B_HUB_4 = 0x80,
 PORT_B_HUB_5 = 0xA0
}PortBHubAddr_e;

// Holds command offset 
typedef enum {
    READ_ANALOG = 0x6, // 12 bits
}PortBHubRegReadOffset_e;

typedef enum {
    WRITE_PWM = 0x3, // 8 bits
}PortBHubRegWriteOffset_e;