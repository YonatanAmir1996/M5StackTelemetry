import os
import sys
import struct
import time
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import RectBivariateSpline
# Determine the root directory based on the current file's location
# and append it to the system's path list to ensure correct module imports.
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../")
sys.path.append(root_path)

# Import necessary modules and classes from the CLI package.
from CLI.Assets.CommandHandler import CommandHandler, PbHubPortAddr_e
from CLI.Devices.DeviceAbs import Device_e
from CLI.Devices.Fsr import Fsr
from CLI.Devices.Imu import Imu
from CLI.Devices.ToF import ToF
from CLI.Devices.Amg8833 import Amg8833
from CLI.Devices.HRU import HRU


class M5Telemetry:

    def __init__(self, plot_amg: bool = False):
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

    def update_values(self, sensors_list: list):
        sensor_bitmap = 0
        for device in sensors_list:
            sensor_bitmap |= 1 << device.value
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

    def rescan(self, button_pb_hub_addr: PbHubPortAddr_e,
               fsr_pb_hub_addr: PbHubPortAddr_e = PbHubPortAddr_e.PORT_1,
               vibration_motor_pb_hub_addr: PbHubPortAddr_e = PbHubPortAddr_e.PORT_2,
               is_rgb_connected: bool = True):
        """
        Rescan devices
        :param button_pb_hub_addr: button pb hub addr
        :param fsr_pb_hub_addr:  fsr pb hub addr
        :param vibration_motor_pb_hub_addr:  vibration motor pb hub addr
        :param is_rgb_connected: is rgb connected to port B
        :return:
        """
        self.__command_handler.command_rescan_sensors(button_pb_hub_addr, fsr_pb_hub_addr, vibration_motor_pb_hub_addr,
                                                      is_rgb_connected)
        print("rescanned devices successfully !")

    def command_set_rgb(self, id: int = 0, red: int = 0, green: int = 0, blue: int = 0):
        """

        :param id: led id
        :param red: 0-100
        :param green: 0-100
        :param blue: 0-100
        :return:
        """
        self.__command_handler.command_set_rgb(id, red, green, blue)
        time.sleep(0.2)

    def command_set_motor(self, duty_cycle: int=50):
        """
        sets motor duty cycle
        :param duty_cycle:
        :return:
        """
        self.__command_handler.command_set_motor(duty_cycle)
        print(f"set motor with duty cycle of {duty_cycle}")
        time.sleep(0.1)

    def plot_amg(self, plot_delay_in_seconds: float = 0.1, min_temprature_show: int = 20, max_temprature_show:int = 100,
                 auto_scale:bool = False):
        """Update the thermal matrix visualization."""
        # Initialize the plot for thermal matrix visualization
        fig, ax = plt.subplots()
        plt.ion()  # Enable interactive mode
        dummy_data = np.zeros((256, 256))
        img = ax.imshow(dummy_data, cmap='jet', interpolation='none', vmin=min_temprature_show, vmax=max_temprature_show)
        cbar = plt.colorbar(img, ax=ax)

        while True:
            self.update_values([Device_e.AMG833])
            # Get the 8x8 matrix
            matrix_8x8 = self.amg.pixels

            # Interpolate the 8x8 matrix to a denser 256x256 matrix
            x = np.linspace(0, 7, 8)
            y = np.linspace(0, 7, 8)
            f = RectBivariateSpline(x, y, matrix_8x8)
            xnew = np.linspace(0, 7, 256)
            ynew = np.linspace(0, 7, 256)
            matrix_256x256 = f(xnew, ynew)

            # Update the displayed data with the new matrix
            img.set_data(matrix_256x256)
            if auto_scale:
                img.autoscale()

            # Redraw the plot to reflect the changes
            fig.canvas.draw()
            plt.pause(plot_delay_in_seconds)  # Add a brief pause

    def plot_tof(self, plot_delay_in_seconds: float = 0.1, min_distance_in_mm: int = 0, max_distance_in_mm: int = 4000,
                 auto_scale:bool = False):
        """Update the ToF matrix visualization."""

        # Initialize the plot for ToF matrix visualization
        fig, ax = plt.subplots()
        plt.ion()  # Enable interactive mode

        # Create dummy data for initializing the visualization
        dummy_data = np.zeros((256, 256))
        img = ax.imshow(dummy_data, cmap='hot', interpolation='none', vmin=min_distance_in_mm, vmax=max_distance_in_mm)  # using 'hot' colormap here
        cbar = plt.colorbar(img, ax=ax)
        cbar.set_label('Distance (mm)')

        while True:
            # Update ToF sensor values
            self.update_values([Device_e.TOF])

            # Get the 8x8 matrix of ToF distances
            matrix_8x8 = self.tof.mm_distances

            # Interpolate the 8x8 matrix to a denser 256x256 matrix for visualization
            x = np.linspace(0, 7, 8)
            y = np.linspace(0, 7, 8)
            f = RectBivariateSpline(x, y, matrix_8x8)
            xnew = np.linspace(0, 7, 256)
            ynew = np.linspace(0, 7, 256)
            matrix_256x256 = f(xnew, ynew)

            # Update the displayed data with the new interpolated matrix
            img.set_data(matrix_256x256)
            if auto_scale:
                img.autoscale()

            # Pause for a specified delay before updating again
            plt.pause(plot_delay_in_seconds)
