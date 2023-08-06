#ifndef IMU_H
#define IMU_H

#include "DeviceAbs.h"

class IMU: public DeviceAbs 
{
    public:
        IMU();
        bool begin()  override;
        void update() override;
        void print()  override;

};

#endif