#ifndef M5_TELEMETRY_H
#define M5_TELEMETRY_H

#include "IMU.h"
#include "PaHub.h"
#include "PulseOximeterSensor.h"
#include "Amg8833.h"
#include "ToF.h"

// Class M5 telemetry
class M5Telemetry 
{
    public:
        M5Telemetry();
        ~M5Telemetry(); 
        void begin(); 
        void standAlonePrint();
        void scan();
        void update();

    public:
        RunningMode_e       runningMode;  

    private:
        DeviceAbs           *pDeviceHandlers[DEVICE_MAX_DEVICES];
        IMU                 imuDevice;
        PulseOximeterSensor pulseOximeterDevice;
        Amg8833             gridEyeSensor;
        ToF                 tofSensor;

};

extern M5Telemetry M5Tel;

#endif