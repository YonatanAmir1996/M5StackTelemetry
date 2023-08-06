#ifndef PA_HUB_H
#define PA_HUB_H

#include "I2CDeviceAbs.h"

class PaHub : public I2CDeviceAbs
{

    public:
        PaHub();
        void scan();

    public:
        PaHubPort_e i2cAddrToPortMap[MAX_I2C_ADDR]; // Mapping between I2C address to the port it is connected
};

extern PaHub PortAHub;
#endif