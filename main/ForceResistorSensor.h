#ifndef FORCE_RESISTOR_SENSOR_H
#define FORCE_RESISTOR_SENSOR_H

#include <M5CoreS3.h>
#include "DeviceAbs.h"

/**
 * @class ForceResistorSensor
 * @brief FSR-402 Interface
 * @details Must be connected to pbhub
 */
class ForceResistorSensor : public DeviceAbs
{

    public:
        ForceResistorSensor();
        void update() override;
        bool begin(uint8_t addr) override;
        void print() override;

    private:
        uint8_t  hubAddr;
        uint16_t fsrValue;
        bool     outputWasSet;
};

#endif
