import os
import sys
import time

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

# Import necessary classes and enums from respective modules
from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e


def poll_devices(m5_telemetry_interface: M5Telemetry, to_set: bool):
    """
    This function polls various devices to retrieve and possibly set new data.
    :param m5_telemetry_interface: The M5Telemetry object used for getting and setting data.
    :param to_set: A boolean that decides whether to set new data or not.
    """
    # Retrieves data from specified devices (TOF, IMU, FSR, AMG833)
    m5_telemetry_interface.update_values([Device_e.TOF, Device_e.IMU, Device_e.FSR, Device_e.AMG833])

    # Print results from sensors. Users may use the results from devices for further operations.
    print(m5_telemetry_interface.fsr)  # Accessing the 'fsr' attribute from M5Telemetry object.
    print(m5_telemetry_interface.imu)  # Accessing the 'imu' attribute from M5Telemetry object.
    print(m5_telemetry_interface.amg)  # Accessing the 'amg' attribute from M5Telemetry object.
    print(m5_telemetry_interface.tof)  # Accessing the 'tof' attribute from M5Telemetry object.

    if to_set is True:
        # Setting values on various devices through the M5Telemetry object.
        m5_telemetry_interface.command_set_speaker()
        m5_telemetry_interface.command_set_rgb(0, 100, 0, 0)
        m5_telemetry_interface.command_set_motor(50)
    else:
        # Resetting RGB and motor values to default through the M5Telemetry object.
        m5_telemetry_interface.command_set_rgb(0, 0, 0, 0)
        m5_telemetry_interface.command_set_motor(0)


if __name__ == '__main__':
    # Creating an instance of the M5Telemetry class.
    interface = M5Telemetry()

    # Rescanning various devices to set their addresses.
    interface.rescan(button_pb_hub_addr=PbHubPortAddr_e.PORT_0,
                     fsr_pb_hub_addr=PbHubPortAddr_e.PORT_1,
                     vibration_motor_pb_hub_addr=PbHubPortAddr_e.PORT_3,
                     speaker_pb_hub_addr=PbHubPortAddr_e.PORT_5,
                     is_rgb_connected=True)
    set_output = True
    while True:
        # Continuously poll devices and possibly set new values based on the set_output flag.
        poll_devices(interface, set_output)
        set_output = not set_output  # Toggle the set_output flag.
        time.sleep(2)  # Sleep for 2 seconds before polling the devices again.