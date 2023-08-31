import os
import sys
import time
import numpy as np

# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e

threshold_in_mm = 50


def contains_values_below_threshold(matrix, threshold):
    return np.any(matrix < threshold)


if __name__ == '__main__':
    interface = M5Telemetry()
    output_was_used = False
    interface.command_set_rgb(0, 100, 0, 0)
    interface.command_set_rgb(1, 0, 100, 0)
    interface.command_set_rgb(2, 0, 0, 100)
    while True:
        interface.update_values(1 << Device_e.TOF.value)
        if contains_values_below_threshold(interface.tof.mm_distances, threshold_in_mm) and not output_was_used:
            interface.command_set_motor(50)
            output_was_used = True
        else:
            if output_was_used:
                interface.command_set_motor(0)
                output_was_used = False
