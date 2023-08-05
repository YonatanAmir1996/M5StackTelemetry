
#ifndef DEVICE_ABS_H
#define DEVICE_ABS_H

#include "SharedDefines.h"

class DeviceAbs {
    public:
        virtual bool begin();
        virtual void update();
        virtual void print();

    protected:
        DeviceName_e     deviceName;
        ConnectionType_e whereCanConnectDevice;
        DeviceType_e     deviceType;
};

#endif