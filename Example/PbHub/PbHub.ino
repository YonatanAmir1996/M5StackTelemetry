/*
    Description: Use Pbhub to read the analog input value of the slave device,
   or drive multiple sets of RGB LEDs.
*/
#include <M5CoreS3.h>
#include "porthub.h"
#include <Adafruit_NeoPixel.h>
#define RGB_PIN 9 // port b
#define motor_pin 12 // PB_HUB OUTPUT PORT
int freq       = 10000;
int ledChannel = 0;
int resolution = 10;

#define X_OFFSET 10
#define Y_OFFSET 18

PortHub porthub;
uint8_t HUB_ADDR[6] = {HUB1_ADDR, HUB2_ADDR, HUB3_ADDR,
                       HUB4_ADDR, HUB5_ADDR, HUB6_ADDR};

#define PIN       9  //定义NeoPixel的控制引脚
#define NUMPIXELS 3   //定义NeoPixel控制灯灯数量

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    NUMPIXELS, RGB_PIN,
    NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.
                            // 设置灯的数量,控制引脚编号,灯灯类型


void setup() {
    M5.begin(true, true, true);
    porthub.begin();
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(4);
    ledcSetup(
        ledChannel, freq,
        resolution);  // Sets the frequency and number of counts corresponding
                      // to the channel.  设置通道对应的频率和计数位数
   /* ledcAttachPin(motor_pin, ledChannel);  // Binds the specified channel to the specified I/O port
                      // for output.  将指定通道绑定到指定 IO 口上以实现输出
                      */
    pixels.begin();         // Init the NeoPixel library.  初始化NeoPixel库
}

void loop() {
    M5.Lcd.clear(BLACK);
    pixels.setPixelColor(0, pixels.Color(100, 0, 0));  // Bright red
    pixels.setPixelColor(1, pixels.Color(0, 100, 0));  // Bright green
    pixels.setPixelColor(2, pixels.Color(0, 0, 100));  // Bright blue
    pixels.show();  // sends the updated color to the hardware.
                    // 将更新后的颜色发送到硬件。
    porthub.hub_a_wire_value_A(HUB1_ADDR, 512);
    delay(1000);
    porthub.hub_a_wire_value_A(HUB1_ADDR, 0);
    delay(1000);
}