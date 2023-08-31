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
    """
    Represents a Time-of-Flight (ToF) device.
    """

    # Number of pixels for the ToF sensor
    tof_num_of_pixels = 64

    def __init__(self):
        """
        Initialize the ToF device.
        """
        # Initialize the base class
        super().__init__(DeviceAbs.Device_e.TOF)

        # Initialize the mm_distances as an 8x8 numpy matrix filled with zeros
        self.mm_distances = np.zeros((8, 8), dtype=np.uint16)

    def set(self, data: bytes):
        """
        Set the distance values by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the ToF data.
        """
        # Unpack the byte sequence as 64 Little Endian 16-bit unsigned integers,
        # reshape it to a 8x8 matrix, and store in mm_distances
        self.mm_distances = np.array(struct.unpack(f"<{ToF.tof_num_of_pixels}H", data)).reshape(8, 8)

    def __str__(self):
        """
        Returns a string representation of the ToF instance as an 8x8 matrix.
        """
        # Convert the matrix to a formatted string
        return f"ToF distances[mm] 8x8:\n{np.array2string(self.mm_distances)}"