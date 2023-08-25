#include "Vibration.h"
#include "PbHubDevice.h"

Vibration vibrationMotor;

Vibration::Vibration() :
hubAddr(PB_HUB_PORT_INVALID_ADDR)
{

}

bool Vibration::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}

void Vibration::setMotor(uint8_t dutyCycle)
{
    PbHub.setPwm(hubAddr, dutyCycle);
}