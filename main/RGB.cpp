#include "RGB.h"

#define PIN       9
#define NUMPIXELS 3

RGB::RGB()
{
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
}

RGB::~RGB() {}

void RGB::SetRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue)
{
    pixels.setPixelColor(id, pixels.Color(red, green, blue));
    pixels.show(); 
}