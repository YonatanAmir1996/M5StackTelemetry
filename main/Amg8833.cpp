#include <M5CoreS3.h>
#include "Amg8833.h"

Amg8833::Amg8833() :
PaHubDeviceAbs(AMG8833_I2C_ADDR)
{

}

Amg8833::~Amg8833()
{

}

bool Amg8833::begin()
{
    return gridEye.begin();
}

void Amg8833::update()
{
    switchPort();
    gridEye.readPixels(pixels);
}

void Amg8833::print()
{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextFont(1);
    M5.Lcd.printf("GridEye:\n");
    for(uint8_t i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i += 8)
    {
        M5.Lcd.printf("[%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f]\n",
                       pixels[i],     pixels[i + 1], pixels[i + 2], pixels[i + 3],
                       pixels[i + 4], pixels[i + 5], pixels[i + 6], pixels[i + 7]);
    }
}