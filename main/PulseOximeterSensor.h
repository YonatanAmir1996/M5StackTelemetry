#ifndef PULSE_OXIMETER_H
#define PULSE_OXIMETER_H

#include "I2CDeviceAbs.h"
#include "MAX30100_PulseOximeter.h"

class PulseOximeterSensor : public I2CDeviceAbs {
    public:
        PulseOximeterSensor();
        bool begin()  override;
        void update() override;
        void print()  override;

    private:
        PulseOximeter pox; 
};

#endif