#ifndef SPEAKER_H
#define SPEAKER_H

#include "DeviceAbs.h"

/**
 * @class Speaker
 * @brief Interface with digital active buzzer
 * @details Interface with digital active buzzer connected to PBHUb
 */
class Speaker: public DeviceAbs 
{
    public:
        Speaker();
        bool begin(uint8_t hubAddr) override;
        void setSpeaker(bool setOrClear);
    private:
        uint8_t hubAddr;
};

#endif