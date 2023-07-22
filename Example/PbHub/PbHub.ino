/*
    Description: Use Pbhub to read the analog input value of the slave device,
   or drive multiple sets of RGB LEDs.
*/
#include <M5CoreS3.h>
#include "porthub.h"

#define X_OFFSET 10
#define Y_OFFSET 18

PortHub porthub;
uint8_t HUB_ADDR[6] = {HUB1_ADDR, HUB2_ADDR, HUB3_ADDR,
                       HUB4_ADDR, HUB5_ADDR, HUB6_ADDR};

void setup() {
    M5.begin(true,true,true);
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("FSR Value: ");
}
uint8_t i = 0;
void loop() {
    uint16_t retVal =  porthub.hub_a_read_value(HUB1_ADDR);
    M5.Lcd.setCursor(30, 40, 2);
    M5.Lcd.fillRect(30, 40, 280, 40, BLACK);
    M5.Lcd.println(retVal);
    if (i % 8 == 0)
    {
        porthub.hub_a_wire_value_B(HUB2_ADDR, 50);
    }
    else if(i % 8 == 4)
    {
        porthub.hub_a_wire_value_B(HUB2_ADDR, 0);
    }
    i++;
    delay(250);
}