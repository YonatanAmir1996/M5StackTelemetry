#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>
#include "DeviceAbs.h"
class RGB: public DeviceAbs 
{
    public:
        RGB();
        ~RGB();

        bool begin() override;

        void SetRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue);
    private:
        Adafruit_NeoPixel pixels;
        uint8_t isConnected;

};

extern RGB RGBDevice;

#endif // RGB_H