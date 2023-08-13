#include <M5CoreS3.h>
#include "ToF.h"

#define TOF_MAX_ARRAY_SIZE 64


/**
 * @brief Default constructor for the ToF class.
 *
 * Initializes image width, resolution, and sets the maximum resolution for the ToF sensor.
 */
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

 
/**
 * @brief Initialize the ToF sensor.
 * @return Returns true if initialization was successful, false otherwise.
 */
bool ToF::begin()
{
    bool    canBegin = false;
    uint8_t count = 0;

    setFrequency(I2C_FREQ_100KHZ);
    
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

/**
 * @brief Update the ToF readings.
 */
void ToF::update()
{
    setFrequency(I2C_FREQ_100KHZ);
    switchPort();
    if (myImager.isDataReady())
    {
        myImager.getRangingData(&measurementData); // RangingData
    }
}


/**
 * @brief Display the ToF readings.
 * 
 * This method prints the ToF data to the M5 LCD in a structured format.
 */
void ToF::print()
{
    M5.Lcd.clear();
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
    delay(100);
}