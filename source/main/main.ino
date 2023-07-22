#include <M5CoreS3.h>

/* After M5CoreS3 is started or reset the program in the setUp()
function will be run, and this part will only be run once.
*/
void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3. 
    M5.Lcd.setTextSize(2);        // Set text size. 
    M5.Lcd.setCursor(0, 0);       // Set the cursor.
    delay(200);                   // Delay 200ms.  
    M5.IMU.Init();                // Init IMU. 
}

void loop() {
    M5.IMU.Update();  
    M5.Lcd.setCursor(30, 30);
    M5.Lcd.printf("Made by Yonatan Amir\n");
    delay(10);
}