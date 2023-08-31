import os
import sys
# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e
import time

if __name__ == '__main__':
    interface = M5Telemetry()
    interface.rescan(PbHubPortAddr_e.PORT_0, PbHubPortAddr_e.PORT_5, PbHubPortAddr_e.PORT_3, True)
    while True:
        for i in range(10):
            sensor_bmp = 1 << Device_e.TOF.value | 1 << Device_e.IMU.value | 1 << Device_e.FSR.value
            print(f"{sensor_bmp:X}")
            interface.update_values(sensor_bmp)
            print(interface.fsr)
            print(interface.imu)
            print(interface.amg)
            print(interface.tof)
            time.sleep(1)



