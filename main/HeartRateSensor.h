#ifndef PULSE_OXIMETER_H
#define PULSE_OXIMETER_H

#include "PaHubDeviceAbs.h"
#include "MAX30100_PulseOximeter.h"

class HeartRateSensor : public PaHubDeviceAbs
{
    public:
        HeartRateSensor();
        bool begin()  override;
        void update() override;
        void print()  override;
        bool restart() override;
        void shutdown();
        void setFrequency();

    private:
        uint32_t      tsLastReport;
        PulseOximeter pox;
};

#endif