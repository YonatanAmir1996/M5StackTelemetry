#include <M5CoreS3.h>
#include "Button.h"
#include "PbHubDevice.h"

Button::Button() :
hubAddr(0)
{

}

bool Button::begin(uint8_t addr)
{
    hubAddr = addr;
    return true;
}

bool Button::IfButtonPressed()
{
    uint32_t count = 0;

    while(PbHub.readAnalogVal(hubAddr) != 0)
    {
        count++;
        delay(1);
    }

    return (count > 0);
}