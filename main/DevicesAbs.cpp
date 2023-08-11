#include "DeviceAbs.h"

bool DeviceAbs::begin()
{
    return true;
}

bool DeviceAbs::begin(uint8_t addr)
{
    return true;
}

bool DeviceAbs::restart() 
{
    return true;
}

void DeviceAbs::update()    {}
void DeviceAbs::print()     {}
void DeviceAbs::shutdown()  {}
