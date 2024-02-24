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
        bool begin(uint8_t addr, DeviceName_e deviceName);
        void print() override;
        uint32_t writeIntoTxBuffer(uint32_t offset) override;

    private:
        DeviceName_e name;
        uint8_t      hubAddr;
        uint16_t     fsrValue;
        bool         outputWasSet;
};

#endif
