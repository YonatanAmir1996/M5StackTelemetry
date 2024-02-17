#ifndef BUTTON_H
#define BUTTON_H

#include "DeviceAbs.h"


/**
 * @class Button
 * @brief Interface with analog button which connected to PBHUB
 * @details Interface with analog button which connected to PBHUB.
 */
class Button : public DeviceAbs
{
    public:
        Button();
        bool IfButtonPressed();
        bool begin(uint8_t hubAddr) override;

    private:
        uint8_t consecutiveClicks;
        uint8_t hubAddr;
};

#endif