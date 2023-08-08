#include <M5CoreS3.h>
#include "PbHubDevice.h"



#define PB_HUB_PORT_0_ADDR               0x40
#define PB_HUB_PORT_1_ADDR               0x50
#define PB_HUB_PORT_2_ADDR               0x60
#define PB_HUB_PORT_3_ADDR               0x70
#define PB_HUB_PORT_4_ADDR               0x80
#define PB_HUB_PORT_5_ADDR               0xA0

PbHubDevice PbHub;

PbHubDevice::PbHubDevice() :
buttonHubPortAddr(PB_HUB_PORT_0_ADDR),
PaHubDeviceAbs(PB_HUB_I2C_ADDR)
{

}

PbHubDevice::~PbHubDevice()
{

}

bool PbHubDevice::begin()
{
    return true;
}

uint16_t PbHubDevice::readAnalogVal(uint8_t addr) {
    uint8_t RegValue_L = 0;
    uint8_t RegValue_H = 0;
    uint8_t error;
    switchPort();
    USBSerial.printf("Switched to port %u\n", getPort());
    Wire.beginTransmission(getBaseAddr());
    Wire.write(addr | 0x06);
    error = Wire.endTransmission();
    USBSerial.printf("error ? %u\n", error);
    

    Wire.requestFrom(getBaseAddr(), (uint8_t)2);
    while (Wire.available()) {
        RegValue_L = Wire.read();
        RegValue_H = Wire.read();
    }
    USBSerial.printf("data read %u\n", (RegValue_H << 8) | RegValue_L);
    return (RegValue_H << 8) | RegValue_L;
}

bool PbHubDevice::IfButtonPressed()
{
    return (readAnalogVal(buttonHubPortAddr) != 0);
}