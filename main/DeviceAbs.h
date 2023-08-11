
#ifndef DEVICE_ABS_H
#define DEVICE_ABS_H

#include "SharedDefines.h"

#define NUMBER_OF_BEGIN_TRIES 3


class DeviceAbs {
    public:
        virtual bool begin();
        virtual bool begin(uint8_t addr);
        virtual void update();
        virtual void print();
        virtual bool restart();
        virtual void shutdown();

    protected:
        DeviceName_e     deviceName;
        ConnectionType_e whereCanConnectDevice;
        DeviceType_e     deviceType;
};

#endif