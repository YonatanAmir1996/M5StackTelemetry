#ifndef PB_HUB_H
#define PB_HUB_H
#include "PaHubDeviceAbs.h"

class PbHubDevice: public PaHubDeviceAbs
{
    public:
        PbHubDevice();
        ~PbHubDevice();
        bool begin() override;
        bool IfButtonPressed();

    private:
        uint16_t readAnalogVal(uint8_t addr);

    private:
        uint8_t buttonHubPortAddr;
};

extern PbHubDevice PbHub;
#endif