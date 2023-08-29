#ifndef M5_TELEMETRY_H
#define M5_TELEMETRY_H

#include "IMU.h"
#include "HeartRateSensor.h"
#include "Amg8833.h"
#include "ToF.h"
#include "Button.h"
#include "ForceResistorSensor.h"

// Class M5 telemetry
class M5Telemetry 
{
    public:
        M5Telemetry();
        ~M5Telemetry(); 
        void begin(); 
        void standAlonePrint(bool standAloneUpdate);
        void scan(uint8_t buttonHubAddr, uint8_t fsrAddr, uint8_t vibrationMotorAddress, bool useRgb);
        void update();
        void scanPaHub();
        void run(bool forceStandAlone, uint8_t buttonHubAddr, uint8_t fsrAddr, uint8_t vibrationMotorAddress, bool useRgb);   
        static void thread(void* pvParameters);

    private:
        void runCommand(uint32_t bitmap);
        void slaveHandler();

    private:
        RunningMode_e       runningMode; 
        DeviceAbs           *pDeviceHandlers[DEVICE_MAX_DEVICES];
        IMU                 imuDevice;
        HeartRateSensor     pulseOximeterDevice;
        Amg8833             gridEyeSensor;
        ToF                 tofSensor;
        PaHubPort_e         i2cAddrToPortMap[MAX_I2C_ADDR]; // Mapping between I2C address to the port it is connected
        Button              button;
        ForceResistorSensor fsr;
        uint32_t            supportedBitmap;
};

extern M5Telemetry M5Tel;

#endif