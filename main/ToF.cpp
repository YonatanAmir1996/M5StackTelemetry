#include <M5CoreS3.h>
#include "ToF.h"

#define TOF_MAX_ARRAY_SIZE 64

ToF::ToF() :
imageWidth(0),
imageResolution(0),
maxRes(TOF_MAX_ARRAY_SIZE),
PaHubDeviceAbs(VL3L5CX_TOF_I2C_ADDR)
{

}

ToF::~ToF()
{

}

bool ToF::begin()
{
    bool    canBegin = false;
    uint8_t count = 0;
    
    while(!canBegin && (count < NUMBER_OF_BEGIN_TRIES))
    {
        canBegin = myImager.begin();
        if(canBegin)
        {
            myImager.setResolution(maxRes); //Enable all 64 pads
            imageResolution = myImager.getResolution(); //Query sensor for current resolution - either 4x4 or 8x8
            imageWidth = sqrt(imageResolution); //Calculate printing width
            myImager.startRanging();
        }
        else
        {
            count++;
        }
        delay(100);
    }

    return (count < NUMBER_OF_BEGIN_TRIES);
}

void ToF::update()
{
    switchPort();
    if (myImager.isDataReady())
    {
        myImager.getRangingData(&measurementData); // RangingData
    }
}


void ToF::print()
{
    switchPort();
    if (myImager.isDataReady())
    {
        myImager.getRangingData(&measurementData); // RangingData
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0,0);
        M5.Lcd.setTextFont(2);
        M5.Lcd.printf("ToF:\n");
        M5.Lcd.setTextFont(1);
        //The ST library returns the data transposed from zone mapping shown in datasheet
        //Pretty-print data with increasing y, decreasing x to reflect reality
        for (int y = 0 ; y <= imageWidth * (imageWidth - 1) ; y += imageWidth)
        {
            M5.Lcd.print("[ ");
            for (int x = imageWidth - 1 ; x >= 0 ; x--)
            {
                
                M5.Lcd.print(measurementData.distance_mm[x + y]);
                M5.Lcd.print(" ");
            }
            M5.Lcd.print("]");
            M5.Lcd.println();
        }
    }
    delay(100);
}