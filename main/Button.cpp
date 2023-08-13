#include <M5CoreS3.h>
#include "Button.h"
#include "PbHubDevice.h"

/**
 * @brief Constructor for the Button class.
 * @details Initializes the Button object with hubAddr set to 0.
 */
Button::Button() :
hubAddr(0)
{

}

/** 
 * @brief Initializes the Button with a specific address.
 * @param addr The address to set for the button.
 * @return true since the operation is always successful.
 */
bool Button::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}


/** 
 * @brief Checks if the button is pressed.
 * @return true if the button is pressed, false otherwise.
 * @details Reads the analog value of the button and checks if it's pressed.
 */
bool Button::IfButtonPressed()
{
    bool     retVal = false;
    uint16_t count = 0;

    while(PbHub.readAnalogVal(hubAddr) != 0)
    {
        count++;
    }
    return count > 0;
}