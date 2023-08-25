#include "M5Telemetry.h"
#include "SharedDefines.h"

void setup()
{
    M5Tel.begin();
    M5Tel.scan(PB_HUB_PORT_0_ADDR, PB_HUB_PORT_1_ADDR, PB_HUB_PORT_3_ADDR, true);
}

void loop()
{
   M5Tel.standAlonePrint(false); 
}