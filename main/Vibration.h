#ifndef VIBRATION_H
#define VIBRATION_H

#include "DeviceAbs.h"

class Vibration : public DeviceAbs
{
    public:
        Vibration();

        bool begin(uint8_t addr) override;
        void setMotor(uint8_t dutyCycle);

    private:
        uint8_t hubAddr;
};

extern Vibration vibrationMotor;

#endif // VIBRATION_H