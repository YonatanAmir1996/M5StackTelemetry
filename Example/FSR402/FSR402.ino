#include <M5CoreS3.h>

constexpr uint8_t analogPin = 8;

void setup()
{
    M5.begin();
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("FSR Value: ");
   // pinMode(analogPin, OUTPUT);
}

void loop()
{
    uint16_t retVal = analogRead(analogPin);
    M5.Lcd.setCursor(30, 40, 2);
    M5.Lcd.fillRect(30, 40, 280, 40, BLACK);
    M5.Lcd.println(retVal);
    delay(250);

}