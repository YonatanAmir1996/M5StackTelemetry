#ifndef AMG8833_H
#define AMG8833_H

#include <Adafruit_AMG88xx.h>
#include "PaHubDeviceAbs.h"

class Amg8833: public PaHubDeviceAbs
{
    public:
        Amg8833();
        ~Amg8833();
        bool begin()  override;
        void update() override;
        void print()  override;


    private:    
        float            pixels[AMG88xx_PIXEL_ARRAY_SIZE];
        Adafruit_AMG88xx gridEye;
};

#endif