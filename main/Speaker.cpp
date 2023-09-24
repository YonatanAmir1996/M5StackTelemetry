#include <M5CoreS3.h>
#include "Speaker.h"
#include "PbHubDevice.h"

/**
 * @brief Constructor for the Button class.
 * @details Initializes the Button object with hubAddr set to 0.
 */
Speaker::Speaker() :
hubAddr(0)
{

}

/** 
 * @brief Initializes the Button with a specific address.
 * @param addr The address to set for the button.
 * @return true since the operation is always successful.
 */
bool Speaker::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}


/** 
 * @brief Active/turn off buzzer
 * @return None
 * @details set - True | clear - False
 */

void Speaker::setSpeaker()
{
    for(uint8_t i = 0; i < 100; i++)
    {
        PbHub.setDigitalWrite0(hubAddr, HIGH);
        delay(1);
        PbHub.setDigitalWrite0(hubAddr, LOW);
        delay(1);
    }
}