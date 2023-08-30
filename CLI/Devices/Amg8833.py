# Import necessary modules
import os
import sys
import struct

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
        # Initialize the pixels list which will hold the sensor readings
        self.pixels = []

    def set(self, data: bytes):
        """
        Set the pixel values by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the sensor data.
        """
        # Unpack the byte sequence and store them in the pixels list
        self.pixels = list(struct.unpack(f"<{Amg8833.PIXEL_ARRAY_SIZE}f", data))

    def __str__(self):
        """
        Returns a string representation of the AMG88xx instance as an 8x8 matrix.
        """
        matrix_representation = ""
        for i in range(0, Amg8833.PIXEL_ARRAY_SIZE, 8):
            matrix_representation += ' | '.join(['%3.1f' % val for val in self.pixels[i:i + 8]]) + '\n'
        return f"AMG88xx pixel values:\n{matrix_representation}"