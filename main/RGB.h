#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>

class RGB: public DeviceAbs 
{
    public:
        RGB();
        ~RGB();

        void SetRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue);
    private:
        Adafruit_NeoPixel pixels;
        

};

extern RGB rgb;

#endif // RGB_H