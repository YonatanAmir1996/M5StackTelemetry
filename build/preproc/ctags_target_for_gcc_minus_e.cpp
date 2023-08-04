# 1 "D:\\M5StackTelemetry\\Example\\PaHubA\\PaHubA.ino"
/*

*******************************************************************************

* Copyright (c) 2023 by M5Stack

*                  Equipped with M5CoreS3 sample source code

*                          配套  M5CoreS3 示例源代码

* Visit for more information: https://docs.m5stack.com/en/core/CoreS3

* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3

*

* Describe: I2C Scanner.  I2C探测

* Date: 2023/5/5

*******************************************************************************

This program scans the addresses 1-127 continuosly and shows the devices found

on the TFT. 该程序连续扫描地址 1-127 并显示在内部(外部)I2C发现的设备。

*/
# 15 "D:\\M5StackTelemetry\\Example\\PaHubA\\PaHubA.ino"
# 16 "D:\\M5StackTelemetry\\Example\\PaHubA\\PaHubA.ino" 2

# 18 "D:\\M5StackTelemetry\\Example\\PaHubA\\PaHubA.ino" 2




uint32_t tsLastReport = 0;




// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;
uint8_t whichPort = 0;
bool wasInit = false;

void portselectall(uint8_t ports) {
  Wire.beginTransmission(0X70);
  Wire.write(ports&0x3f);
  Wire.endTransmission();
}


//Hub range is 0 to 5
void portselect(uint8_t i) {
  if (i > 7) return;

  Wire.beginTransmission(0X70);
  Wire.write(1 << i);
  Wire.endTransmission();
}


void setup() {
    int error = 0;
  // put your setup code here, to run once:
  M5.begin(true, true, false);
  Wire.begin(2, 1);
  for(int i = 0; i < 6; i++){
     portselect(i);
     M5.Lcd.setCursor(0, i * 40, 2);
     M5.Lcd.print("TCA Port"); M5.Lcd.print(i);
     for(uint8_t address = 1; address < 127; address++){
       Wire.beginTransmission(address);
       error = Wire.endTransmission();
       if(error == 0){
        if((address == 0x70) || (address == 0x75))
        {
          continue;
        }

          if(address == 0x57)
          {
            M5.Lcd.print(":  Found I2C 0x");
            M5.Lcd.print(address,16);
            delay(1000);
            pox.begin();
            wasInit = true;
            M5.Lcd.fillScreen(0x0000 /*   0,   0,   0 */);
            break;
          }
       }else{
          M5.Lcd.setCursor(100, i * 40);
          M5.Lcd.fillRect(100, i * 40, 280, 40, 0x0000 /*   0,   0,   0 */);
       }
      delay(1);
     }
     if(wasInit)
     {
      break;
     }
  }
}

void loop() {
     // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > 100) {
        M5.Lcd.setTextFont(4);
        M5.Lcd.setCursor(10, 30, 4);
        M5.Lcd.print("Heart rate:");
        M5.Lcd.print(pox.getHeartRate());
        M5.Lcd.setCursor(10, 60, 4);
        M5.Lcd.print("bpm / SpO2:");
        M5.Lcd.print(pox.getSpO2());
        M5.Lcd.println("%");

        tsLastReport = millis();
    }
}
