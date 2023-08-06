#ifndef TOF_H
#define TOF_H

#include <SparkFun_VL53L5CX_Library.h> 
#include "PaHubDeviceAbs.h"

class ToF: public PaHubDeviceAbs
{
    public:
        ToF();
        ~ToF();
        bool begin();
        void update();
        void print();

    private:    
        SparkFun_VL53L5CX    myImager;
        VL53L5CX_ResultsData measurementData; // Result data class structure, 1356 byes of RAM
        uint32_t             imageResolution; //Used to pretty print output
        uint32_t             imageWidth;      //Used to pretty print output
        uint8_t              maxRes;
};

#endif