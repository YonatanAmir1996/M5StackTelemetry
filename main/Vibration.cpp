#include "Vibration.h"
#include "PbHubDevice.h"

Vibration vibrationMotor;


/**
 * @brief Default constructor for the Vibration class.
 *
 * Initializes the hub address to an invalid address by default.
 */
Vibration::Vibration() :
hubAddr(PB_HUB_PORT_INVALID_ADDR)
{

}

/**
 * @brief Begin operation of the vibration motor by setting the address.
 * 
 * @param addr The address of the hub.
 * @return Returns true once the address is set.
 */
bool Vibration::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}

/**
 * @brief Set the duty cycle of the vibration motor.
 * 
 * @param dutyCycle The duty cycle for the vibration motor's operation.
 */
void Vibration::setMotor(uint8_t dutyCycle)
{
    PbHub.setPwm(hubAddr, dutyCycle);
}