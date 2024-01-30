import os
import sys
import time
import numpy as np

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

# Import necessary classes and enums from respective modules
from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e


if __name__ == '__main__':
    # Creating an instance of the M5Telemetry class.
    interface = M5Telemetry(is_wifi=False)
    big_array_matrix = []
    # Rescanning various devices to set their addresses.
    interface.rescan(button_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     fsr_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     vibration_motor_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     speaker_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     is_rgb_connected=False)
    interface.update_values([Device_e.TOF])
    big_array_matrix.append(interface.tof.mm_distances)