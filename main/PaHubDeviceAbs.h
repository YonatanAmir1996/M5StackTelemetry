#ifndef PA_HUB_DEVICE_H
#define PA_HUB_DEVICE_H

#include "I2CDeviceAbs.h"

/* Class holds basic methods relevent data to communicate with device by a certain port*/
class PaHubDeviceAbs: public I2CDeviceAbs 
{
    public:
        PaHubDeviceAbs(uint8_t addr);
        ~PaHubDeviceAbs();
        PaHubPort_e  getPort();
        void         setPort(PaHubPort_e port);
        void         switchPort();
        
    private:
        PaHubPort_e  connectedPort; 
};

#endif