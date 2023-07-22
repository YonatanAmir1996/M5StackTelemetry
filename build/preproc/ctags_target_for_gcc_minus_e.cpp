# 1 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino"
# 2 "D:\\M5StackTelemetry\\Example\\FSR402\\FSR402.ino" 2

constexpr uint8_t analogPin = 8;

void setup()
{
    M5.begin();
    M5.Lcd.clear(0x0000 /*   0,   0,   0 */);
    M5.Lcd.setTextColor(0xFFFF /* 255, 255, 255 */);
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
