#ifndef PA_HUB_DEVICE_H
#define PA_HUB_DEVICE_H

#include "I2CDeviceAbs.h"

#define I2C_FREQ_400KHZ 400000
#define I2C_FREQ_100KHZ 100000
/**
 * @brief PaHubDeviceAbs class.
 * 
 * Provides base methods and relevant data to facilitate communication with a device through a specific port.
 */
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