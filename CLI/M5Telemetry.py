import os
import sys
import struct
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../")
sys.path.append(root_path)
from CLI.Assets.CommandHandler import CommandHandler
from CLI.Devices.DeviceAbs import Device_e
from CLI.Devices.Fsr import Fsr
from CLI.Devices.Imu import Imu
from CLI.Devices.ToF import ToF
from CLI.Devices.Amg8833 import Amg8833

class M5Telemetry:


    def __init__(self):
        self.__command_handler = CommandHandler()

        # Devices
        self.fsr = Fsr()
        self.imu = Imu()
        self.tof = ToF()
        self.amg = Amg8833()

        # Map for update values
        self.devices = {
            Device_e.FSR: self.fsr,
            Device_e.IMU: self.imu,
            Device_e.TOF: self.tof,
            Device_e.AMG833: self.amg
        }

    def update_values(self, sensor_bitmap):
        data_stream = self.__command_handler.command_run_sensors(sensor_bitmap)
        size = len(data_stream)
        while size:
            # Number of bytes required to read for device
            temp_size = struct.unpack('<I', data_stream[0:4])[0]
            # device_id
            device_id = struct.unpack('<I', data_stream[4:8])[0]
            # data of device
            data = data_stream[8: 8 + (temp_size - 4)]
            # give stream of bytes in LE of required data for device
            self.devices[Device_e(device_id)].set(data)
            data_stream = data_stream[8 + (temp_size - 4): ]
            size -= temp_size + 4