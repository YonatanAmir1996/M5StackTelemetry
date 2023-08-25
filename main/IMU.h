#ifndef IMU_H
#define IMU_H

#include "DeviceAbs.h"

/**
 * @brief IMU (Inertial Measurement Unit) class.
 * 
 * Provides functionalities to interact with the IMU device, including initialization, data updating, 
 * and data display.
 */
class IMU: public DeviceAbs 
{
    public:
        IMU();
        bool begin()  override;
        void update() override;
        void print()  override;

};

#endif