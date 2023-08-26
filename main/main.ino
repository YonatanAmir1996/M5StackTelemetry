#include "M5Telemetry.h"
#include "SharedDefines.h"

void setup()
{
    M5Tel.begin();
}

void loop()
{
    M5Tel.run(
        false,              // Force standalone flag
        /* Standalone parameters in case of force standalone / failure connect to RASPBERRY PI*/
        PB_HUB_PORT_0_ADDR, // Button PbHub address
        PB_HUB_PORT_1_ADDR, // FSR PbHub address
        PB_HUB_PORT_3_ADDR, // Vibration Motor PbHub address
        true                // use RGB device(Supported only in PORT B)
        );
}