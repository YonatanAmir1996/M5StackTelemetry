#ifndef M5_TELEMETRY_H
#define M5_TELEMETRY_H

#include "DeviceAbs.h"
#include "IMU.h"
#include "PulseOximeterSensor.h"

// Class M5 telemetry
class M5Telemetry 
{
    public:
        M5Telemetry();
        ~M5Telemetry();
    
    private:
        void scan();


    public:
        RunningMode_e       runningMode;  

    private:
        DeviceAbs           *pDeviceHandlers[DEVICE_MAX_DEVICES];
        IMU                 imuDevice;
        PulseOximeterSensor pulseOximeterDevice;

};

extern M5Telemetry M5Tel;

#endif