import os
import sys
import struct

# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../")
sys.path.append(root_path)

# Import necessary modules and classes from the CLI package.
from CLI.Assets.CommandHandler import CommandHandler
from CLI.Devices.DeviceAbs import Device_e
from CLI.Devices.Fsr import Fsr
from CLI.Devices.Imu import Imu
from CLI.Devices.ToF import ToF
from CLI.Devices.Amg8833 import Amg8833
from CLI.Devices.HRU import HRU


class M5Telemetry:

    def __init__(self):
        # Create an instance of CommandHandler to handle commands.
        self.__command_handler = CommandHandler()

        # Initialize devices.
        self.fsr = Fsr()
        self.imu = Imu()
        self.tof = ToF()
        self.amg = Amg8833()
        self.hru = HRU()

        # Mapping of Device enums to device instances for easy updating of device values.
        self.devices = {
            Device_e.FSR: self.fsr,
            Device_e.IMU: self.imu,
            Device_e.TOF: self.tof,
            Device_e.AMG833: self.amg,
            Device_e.HRU: self.hru
        }

    def disconnect(self):
        self.__command_handler.disconnect()

    def update_values(self, sensor_bitmap):
        # Get raw data stream for sensors based on the provided sensor_bitmap.
        data_stream = self.__command_handler.command_run_sensors(sensor_bitmap)

        # Get the total size of the data stream.
        size = len(data_stream)

        # Iterate over the data stream and update device values.
        while size:
            # Extract the size of the current device data from the stream.
            temp_size = struct.unpack('<I', data_stream[0:4])[0]

            # Extract the device ID (indicating which device the data belongs to).
            device_id = struct.unpack('<I', data_stream[4:8])[0]

            # Extract the actual device data based on the provided size.
            data = data_stream[8: 8 + (temp_size - 4)]

            # Update the corresponding device's values using the extracted data.
            self.devices[Device_e(device_id)].set(data)

            # Move to the next chunk of data in the data stream.
            data_stream = data_stream[8 + (temp_size - 4):]

            # Reduce the remaining size of the data stream.
            size -= temp_size + 4