#include "RGB.h"
#include <M5CoreS3.h>

#define PIN       9
#define NUMPIXELS 3

RGB RGBDevice;

/**
 * @brief Default constructor for the RGB class.
 * @details Not used yet.
 */
RGB::RGB() : isConnected(false)
{
}

/**
 * @brief Initializes the RGB object and sets the connection status.
 * @details Instantiates the Adafruit_NeoPixel with the given configuration and sets the isConnected flag to true.
 * @return true always
 */
bool RGB::begin()
{
    if(isConnected)
    {
        pixels.clear();
    }
    else
    {
        M5.Axp.powerModeSet(POWER_MODE_USB_IN_BUS_OUT);
        pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    }
    pixels.begin();
    isConnected = true;
    return true;
}

/**
 * @brief Destructor for the RGB class.
 * @details Currently, this destructor does not have any specific tasks to perform.
 */
RGB::~RGB() {}

/**
 * @brief Set the color of a specific pixel.
 * @details Takes an ID for a pixel and RGB values to set the color for that pixel.
 * @param id The ID of the pixel to be set.
 * @param red The red value for the color (0-255).
 * @param green The green value for the color (0-255).
 * @param blue The blue value for the color (0-255).
 */
void RGB::SetRGB(uint8_t id, uint8_t red, uint8_t green, uint8_t blue)
{
    if(isConnected)
    {
        pixels.setPixelColor(id, pixels.Color(red, green, blue));
        pixels.show();
        delay(200);
    }
}