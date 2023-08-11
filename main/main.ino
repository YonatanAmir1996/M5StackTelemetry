#include "M5Telemetry.h"
#include "SharedDefines.h"

void setup()
{
    M5Tel.begin();
    M5Tel.scan(PB_HUB_PORT_0_ADDR, PB_HUB_PORT_1_ADDR);
}

void loop()
{
   M5Tel.standAlonePrint(); 
}