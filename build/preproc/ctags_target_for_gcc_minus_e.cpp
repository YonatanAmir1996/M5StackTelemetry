# 1 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino"
/*

    Description: Use Pbhub to read the analog input value of the slave device,

   or drive multiple sets of RGB LEDs.

*/
# 5 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino"
# 6 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino" 2
# 7 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino" 2
# 8 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino" 2


int freq = 10000;
int ledChannel = 0;
int resolution = 10;




PortHub porthub;
uint8_t HUB_ADDR[6] = {0x40, 0x50, 0x60,
                       0x70, 0x80, 0xA0};




Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    3 /*定义NeoPixel控制灯灯数量*/, 9 /* port b*/,
    ((1 << 6) | (1 << 4) | (0 << 2) | (2)) /*|< Transmit as G,R,B*/ + 0x0000 /*|< 800 KHz data transmission*/); // set number of LEDs, pin number, LED type.
                            // 设置灯的数量,控制引脚编号,灯灯类型


void setup() {
    M5.begin(true, true, true);
    porthub.begin();
    M5.Lcd.clear(0x0000 /*   0,   0,   0 */);
    M5.Lcd.setTextColor(0xFFFF /* 255, 255, 255 */);
    M5.Lcd.setTextSize(4);
    ledcSetup(
        ledChannel, freq,
        resolution); // Sets the frequency and number of counts corresponding
                      // to the channel.  设置通道对应的频率和计数位数
   /* ledcAttachPin(motor_pin, ledChannel);  // Binds the specified channel to the specified I/O port

                      // for output.  将指定通道绑定到指定 IO 口上以实现输出

                      */
# 43 "D:\\M5StackTelemetry\\Example\\PbHub\\PbHub.ino"
                         ledcAttachPin(
        12 /* PB_HUB OUTPUT PORT0*/,
        ledChannel); // Binds the specified channel to the specified I/O port
                      // for output.  将指定通道绑定到指定 IO 口上以实现输出
    pixels.begin(); // Init the NeoPixel library.  初始化NeoPixel库
}

void loop() {
    M5.Lcd.clear(0x0000 /*   0,   0,   0 */);
    pixels.setPixelColor(0, pixels.Color(100, 0, 0)); // Bright red
    pixels.setPixelColor(1, pixels.Color(0, 100, 0)); // Bright green
    pixels.setPixelColor(2, pixels.Color(0, 0, 100)); // Bright blue
    pixels.show(); // sends the updated color to the hardware.
                    // 将更新后的颜色发送到硬件。
    porthub.hub_a_wire_value_A(0x40, 512);
    delay(1000);
    porthub.hub_a_wire_value_A(0x40, 0);
    delay(1000);
}
