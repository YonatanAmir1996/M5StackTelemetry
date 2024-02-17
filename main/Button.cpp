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
    consecutiveClicks = 0;
    return true;
}


/** 
 * @brief Checks if the button is pressed.
 * @return true if the button is pressed, false otherwise.
 * @details Reads the analog value of the button and checks if it's pressed.
 */
bool Button::IfButtonPressed()
{
    if ((PbHub.readAnalogVal(hubAddr) == 0xFFF) && (consecutiveClicks <= 5))
    {
        consecutiveClicks++;
    }
    else
    {
      consecutiveClicks = 0;
    }

    return (consecutiveClicks == 5);
}