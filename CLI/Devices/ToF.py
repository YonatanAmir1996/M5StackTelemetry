# Import necessary modules
import os
import sys
import struct
import numpy as np  # <-- Add this import

# Determine the root path based on the current file's location
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")

# Append the determined root path to the system's path list
# This step ensures that the program can import modules from the parent directory
sys.path.append(root_path)

# Import the DeviceAbs module from the CLI.Devices package
import CLI.Devices.DeviceAbs as DeviceAbs


class ToF(DeviceAbs.DeviceAbs):

    # Number of pixels for the ToF sensor
    tof_num_of_pixels = 64
    history_length = 100  # For example, adjust as needed

    def __init__(self):
        super().__init__(DeviceAbs.Device_e.TOF)
        self.mm_distances = np.zeros((8, 8), dtype=np.uint16)
        self.temp_mm_distances = np.zeros((8, 8), dtype=np.uint16)
        # Initialize history as a list
        self.mm_distances_history = []
        # Initialize the average matrix
        self.mm_distances_avg = np.zeros((8, 8), dtype=np.float64)

    def set(self, data: bytes):
        # Update mm_distances as before
        self.mm_distances = np.array(struct.unpack(f"<{ToF.tof_num_of_pixels}H", data)).reshape(8, 8)

        # Avoid zero distances to prevent issues with the geometric mean
        self.temp_mm_distances = np.where(self.mm_distances == 0, 1e-12, self.mm_distances)

        # Append the current matrix to the history
        self.mm_distances_history.append(self.temp_mm_distances)

        # Keep only the last 'history_length' matrices
        while len(self.mm_distances_history) > ToF.history_length:
            self.mm_distances_history.pop(0)

        # Compute the average matrix
        self.mm_distances_avg = np.mean(self.mm_distances_history, axis=0)

    def __str__(self):
        return f"ToF distances[mm] 8x8:\n{np.array2string(self.mm_distances)}"