#include "M5Telemetry.h"
#include "SharedDefines.h"


// Wifi details are hardcoded
WifiStruct wifiDetails = 
{
    .ssid = "Bar1",
    .password = "0526006314",
    .serverAddress = "192.168.7.7",
    .serverPort = 12345
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
        PB_HUB_PORT_0_ADDR,       // Button PbHub address
        PB_HUB_PORT_1_ADDR,       // FSR PbHub address
        PB_HUB_PORT_3_ADDR,       // Vibration Motor PbHub address
        PB_HUB_PORT_5_ADDR,       // speaker Address
        false,                    // use RGB device(Supported only in PORT B)
        &wifiDetails
        );
}