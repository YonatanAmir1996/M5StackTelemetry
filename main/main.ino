#include "M5Telemetry.h"

void setup()
{
    M5Tel.begin();
    M5Tel.scan();
}

void loop()
{
   M5Tel.update();
   M5Tel.standAlonePrint(); 
}