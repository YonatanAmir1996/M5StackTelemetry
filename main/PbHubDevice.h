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
};

extern PbHubDevice PbHub;
#endif