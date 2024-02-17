#include "M5Telemetry.h"
#include "SharedDefines.h"


// Wifi details are hardcoded
WifiStruct wifiDetails = 
{
    .ssid = "Yonatan",
    .password = "a1234567",
    .serverAddress = "192.168.119.137",
    .serverPort = 9000
};

void setup()
{
    M5Tel.begin();
}

void loop()
{
    M5Tel.run(
        false,                    // Force standalone flag
        /* Standalone parameters in case of force standalone / failure connect to RASPBERRY PI */
        PB_HUB_PORT_4_ADDR,       // Button PbHub address
        PB_HUB_PORT_INVALID_ADDR, // FSR PbHub address
        PB_HUB_PORT_0_ADDR,       // FSR1 PbHub address
        PB_HUB_PORT_INVALID_ADDR, // Vibration Motor PbHub address
        PB_HUB_PORT_INVALID_ADDR, // speaker Address
        false,                    // use RGB device(Supported only in PORT B)
        &wifiDetails,             // Hard coded Wifi detalis
        false,                     // Force stand alone update print screen - True | Print screen via button press - False 
        10000                     // State switch rate in case of standalone
        );
}