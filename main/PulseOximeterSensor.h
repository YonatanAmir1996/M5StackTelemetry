#ifndef PULSE_OXIMETER_H
#define PULSE_OXIMETER_H

#include "PaHubDeviceAbs.h"
#include "MAX30100_PulseOximeter.h"

class PulseOximeterSensor : public PaHubDeviceAbs
{
    public:
        PulseOximeterSensor();
        bool begin()  override;
        void update() override;
        void print()  override;

    private:
        PulseOximeter pox; 
};

#endif