#include <Arduino.h>
#line 1 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino"
#include <M5CoreS3.h>

constexpr uint8_t analogPin = 8;

#line 5 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino"
void setup();
#line 14 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino"
void loop();
#line 5 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino"
void setup()
{
    M5.begin();
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
   // pinMode(analogPin, OUTPUT);
}

void loop()
{
 uint16_t retVal = analogRead(analogPin);
 M5.Lcd.clear();
 M5.Lcd.setCursor(0, 0, 2);
 M5.Lcd.print("FSR Value: ");
 M5.Lcd.println(retVal);
 delay(250);

}
