#ifndef TOF_H
#define TOF_H

#include <SparkFun_VL53L5CX_Library.h> 
#include "PaHubDeviceAbs.h"

/**
 * @brief Time-of-Flight (ToF) Sensor Class.
 * 
 * This class provides methods to interface with the ToF sensor, fetch data, and display the readings.
 */
class ToF: public PaHubDeviceAbs
{
    public:
        ToF();
        ~ToF();
        bool begin() override;
        void update() override;
        void print() override;
        void shutdown() override;
        bool restart() override;
        uint32_t writeIntoTxBuffer(uint32_t offset) override;

    private:    
        SparkFun_VL53L5CX    myImager;               // Instance of the SparkFun VL53L5CX library for interfacing with the ToF sensor
        VL53L5CX_ResultsData measurementData;        // Structure to hold ranging result data
        uint32_t             imageResolution;        // Holds the current image resolution
        uint32_t             imageWidth;             // Width of the image used for printing
        uint8_t              maxRes;                 // Maximum resolution constant
};

#endif