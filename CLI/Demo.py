import os
import sys
# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e

if __name__ == '__main__':
    interface = M5Telemetry()
    for i in range(80):
        interface.update_values(1 << Device_e.HRU)
        print(interface.hru)