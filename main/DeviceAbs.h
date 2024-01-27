
#ifndef DEVICE_ABS_H
#define DEVICE_ABS_H

#include "SharedDefines.h"
#include "CommandHandler.h"
#define NUMBER_OF_BEGIN_TRIES 8


/**
 * @class DeviceAbs
 * @brief Abstract base class for all devices.
 * @details Provides a common interface for all derived device classes.
 */
class DeviceAbs {
    public:
        virtual bool begin();
        virtual bool begin(uint8_t addr);
        virtual void update();
        virtual void print();
        virtual bool restart();
        virtual void shutdown();
        virtual uint32_t writeIntoTxBuffer(uint32_t offset);
        void         setFrequency(uint32_t freq);
};

#endif