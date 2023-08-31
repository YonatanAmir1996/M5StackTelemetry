# Import necessary modules
import os
import sys
import struct
import numpy as np
# Determine the root path based on the current file's location
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")

# Append the determined root path to the system's path list
# This step ensures that the program can import modules from the parent directory
sys.path.append(root_path)

# Import the DeviceAbs module from the CLI.Devices package
import CLI.Devices.DeviceAbs as DeviceAbs


class Amg8833(DeviceAbs.DeviceAbs):
    """
    Represents the AMG88xx sensor which has a pixel array of size 64.
    """

    # Number of pixels for the AMG88xx sensor
    PIXEL_ARRAY_SIZE = 64

    def __init__(self):
        """
        Initialize the AMG88xx sensor.
        """
        # Initialize the base class
        super().__init__(DeviceAbs.Device_e.AMG833)
        # Initialize the pixels as an 8x8 numpy matrix filled with zeros
        self.pixels = np.zeros((8, 8), dtype=float)

    def set(self, data: bytes):
        """
        Set the pixel values by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the sensor data.
        """
        # Unpack the byte sequence and reshape it to a 8x8 matrix
        self.pixels = np.array(struct.unpack(f"<{Amg8833.PIXEL_ARRAY_SIZE}f", data)).reshape(8, 8)

    def __str__(self):
        """
        Returns a string representation of the AMG88xx instance as an 8x8 matrix.
        """
        # Convert the matrix to a formatted string
        formatted_str = np.array2string(self.pixels, formatter={'float_kind': lambda x: "%.1f" % x})

        return f"AMG88xx \N{DEGREE SIGN} 8x8:\n{formatted_str}"