#include "ForceResistorSensor.h"
#include "PbHubDevice.h"

ForceResistorSensor::ForceResistorSensor() :
hubAddr(0),
fsrValue(0)
{
}

bool ForceResistorSensor::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}

void ForceResistorSensor::update()
{
    fsrValue = PbHub.readAnalogVal(hubAddr);
}

void ForceResistorSensor::print()
{
    update();
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0, 2);
    M5.Lcd.print("FSR Value: ");
    M5.Lcd.println(fsrValue);
    delay(100);
}