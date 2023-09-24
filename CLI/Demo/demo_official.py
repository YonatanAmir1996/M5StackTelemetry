import os
import sys
import time
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e


def poll_devices(m5_telemetry_interface: M5Telemetry, to_set: bool):
    m5_telemetry_interface.update_values([Device_e.TOF, Device_e.IMU, Device_e.FSR, Device_e.AMG833])
    print(m5_telemetry_interface.fsr)
    print(m5_telemetry_interface.imu)
    print(m5_telemetry_interface.amg)
    print(m5_telemetry_interface.tof)
    if to_set is True:
        m5_telemetry_interface.command_set_speaker()
        m5_telemetry_interface.command_set_rgb(0, 100, 0, 0)
        m5_telemetry_interface.command_set_motor(50)
    else:
        m5_telemetry_interface.command_set_rgb(0, 0, 0, 0)
        m5_telemetry_interface.command_set_motor(0)


if __name__ == '__main__':
    interface = M5Telemetry()
    interface.rescan(button_pb_hub_addr=PbHubPortAddr_e.PORT_0,
                     fsr_pb_hub_addr=PbHubPortAddr_e.PORT_1,
                     vibration_motor_pb_hub_addr=PbHubPortAddr_e.PORT_3,
                     speaker_pb_hub_addr=PbHubPortAddr_e.PORT_5,
                     is_rgb_connected=True)
    set_output = True
    while True:
        poll_devices(interface, set_output)
        if set_output is True:
            set_output = False
        else:
            set_output = True
        time.sleep(2)



