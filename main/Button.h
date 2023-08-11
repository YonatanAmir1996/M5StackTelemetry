#ifndef BUTTON_H
#define BUTTON_H

#include "DeviceAbs.h"

class Button : public DeviceAbs
{
    public:
        Button();
        bool IfButtonPressed();
        bool begin(uint8_t hubAddr) override;

    private:
        uint8_t hubAddr;
};

#endif