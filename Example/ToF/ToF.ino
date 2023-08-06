/*
  Read an 8x8 array of distances from the VL53L5CX
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 26, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  This example shows how to read all 64 distance readings at once.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/18642

*/

#include <M5CoreS3.h>
#include <SparkFun_VL53L5CX_Library.h> //http://librarymanager/All#SparkFun_VL53L5CX



int imageResolution = 0; //Used to pretty print output
int imageWidth = 0; //Used to pretty print output
uint8_t maxRes = 8*8;

void setup()
{
  m5.begin(true,true,true);
  delay(1000);
  if (myImager.begin() == false)
  {
    M5.Lcd.println(F("Sensor not found - check your wiring. Freezing"));
    while (1) ;
  }
  
  myImager.setResolution(maxRes); //Enable all 64 pads
  
  imageResolution = myImager.getResolution(); //Query sensor for current resolution - either 4x4 or 8x8
  imageWidth = sqrt(imageResolution); //Calculate printing width

  myImager.startRanging();
}

void loop()
{
  //Poll sensor for new data
  if (myImager.isDataReady() == true)
  {
    if (myImager.getRangingData(&measurementData)) //Read distance data into array
    {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.setTextFont(2);
        //The ST library returns the data transposed from zone mapping shown in datasheet
        //Pretty-print data with increasing y, decreasing x to reflect reality
        for (int y = 0 ; y <= imageWidth * (imageWidth - 1) ; y += imageWidth)
        {
            M5.Lcd.print("[");
            USBSerial.print("[");
            for (int x = imageWidth - 1 ; x >= 0 ; x--)
            {
                
                M5.Lcd.print(measurementData.distance_mm[x + y]);
                M5.Lcd.print(",");
                USBSerial.print(",");
                USBSerial.print(measurementData.distance_mm[x + y]);
            }
            M5.Lcd.print("]");
            USBSerial.print("]");
            M5.Lcd.println();
            USBSerial.println();
        }
        USBSerial.println();
    }
  }

  delay(5); //Small delay between polling
}