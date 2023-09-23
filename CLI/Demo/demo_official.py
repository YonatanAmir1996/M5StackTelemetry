import os
import sys
import time
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e


if __name__ == '__main__':
    interface = M5Telemetry()
    interface.rescan(button_pb_hub_addr=PbHubPortAddr_e.PORT_0,
                     fsr_pb_hub_addr=PbHubPortAddr_e.PORT_5,
                     vibration_motor_pb_hub_addr=PbHubPortAddr_e.PORT_3,
                     is_rgb_connected=False)

    while True:
        interface.update_values([Device_e.TOF, Device_e.IMU, Device_e.FSR, Device_e.AMG833])
        print(interface.fsr)
        print(interface.imu)
        print(interface.amg)
        print(interface.tof)
        time.sleep(1)



