#ifndef PB_HUB_H
#define PB_HUB_H
#include "PaHubDeviceAbs.h"

class PbHubDevice: public PaHubDeviceAbs
{
    public:
        PbHubDevice();
        ~PbHubDevice();
        bool begin() override;
        uint16_t readAnalogVal(uint8_t addr);
        void setPwm(uint8_t addr, uint8_t dutyCycle);
        void setDigitalWrite0(uint8_t addr, uint8_t value);
};

extern PbHubDevice PbHub;
#endif