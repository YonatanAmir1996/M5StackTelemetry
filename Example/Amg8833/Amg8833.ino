#include <M5CoreS3.h>
#include <Adafruit_AMG88xx.h>

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
Adafruit_AMG88xx amg;

void setup() {
    
    M5.begin(true,true,true);
    // default settings
    while(!amg.begin())
    {
        M5.Lcd.setTextFont(4);
        M5.Lcd.setCursor(50, 100, 4);
        M5.Lcd.println("Sensor not found");
        delay(1000);
    };
    M5.Lcd.fillScreen(BLACK);
    delay(100); // let sensor boot up
}


void loop() { 
    //read all the pixels
    amg.readPixels(pixels);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextFont(1);
    M5.Lcd.print("[");
    USBSerial.print("[");
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
        M5.Lcd.print(pixels[i-1]);
        M5.Lcd.print(", ");
        if( i%8 == 0 ) M5.Lcd.println("]");
        USBSerial.print(pixels[i-1]);
        USBSerial.print(", ");
        if( i%8 == 0 ) USBSerial.println("]");
    }
    USBSerial.println("");
    M5.Lcd.println("");

    //delay a second
    delay(1000);
}