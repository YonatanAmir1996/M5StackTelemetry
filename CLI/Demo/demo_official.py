import os
import sys
import time

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

# Import necessary classes and enums from respective modules
from CLI.M5Telemetry import M5Telemetry
from CLI.Devices.DeviceAbs import Device_e
from CLI.Assets.CommandHandler import PbHubPortAddr_e


def poll_devices(m5_telemetry_interface: M5Telemetry, to_set: bool, motor_pwm: int, rgb: int):
    """
    This function polls various devices to retrieve and possibly set new data.
    :param m5_telemetry_interface: The M5Telemetry object used for getting and setting data.
    :param to_set: A boolean that decides whether to set new data or not.
    :param motor_pwm: PWM of motor
    """
    # Retrieves data from specified devices (TOF, IMU, FSR, AMG833)
    m5_telemetry_interface.update_values([Device_e.TOF, Device_e.IMU, Device_e.FSR, Device_e.AMG833])
    # Print results from sensors. Users may use the results from devices for further operations.
    print(m5_telemetry_interface.fsr)  # Accessing the 'fsr' attribute from M5Telemetry object.
    print(m5_telemetry_interface.imu)  # Accessing the 'imu' attribute from M5Telemetry object.
    print(m5_telemetry_interface.amg)  # Accessing the 'amg' attribute from M5Telemetry object.
    print(m5_telemetry_interface.tof)  # Accessing the 'tof' attribute from M5Telemetry object.
    if to_set:
        # Setting values on various devices through the M5Telemetry object.
        # m5_telemetry_interface.command_set_speaker()
        m5_telemetry_interface.command_set_rgb(0, rgb, 0, 0)
        # m5_telemetry_interface.command_set_motor(motor_pwm)


if __name__ == '__main__':
    # Creating an instance of the M5Telemetry class.
    interface = M5Telemetry(is_wifi=False)

    # Rescanning various devices to set their addresses.
    interface.rescan(button_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     fsr_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     vibration_motor_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     speaker_pb_hub_addr=PbHubPortAddr_e.INVALID,
                     is_rgb_connected=False)
    start_time = time.time()
    motor_pwm = 0
    rgb = 0
    state = 0
    while True:
        # Continuously poll devices and possibly set new values based on the set_output flag.
        set_output = False
        # Vibration Motor -> 3 seconds off | 1 second on
        if state == 0:
            if (time.time() - start_time) > 3:
                set_output = True  # Toggle the set_output flag.
                motor_pwm = 50
                rgb = 80
                state = 1
                start_time = time.time()
        else:
            if (time.time() - start_time) > 1:
                set_output = True
                motor_pwm = 0
                rgb = 0
                state = 0
                start_time = time.time()
        poll_devices(interface, set_output, motor_pwm, rgb)
