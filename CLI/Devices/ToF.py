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

        # Initialize the mm_distances list which will hold the ToF readings in millimeters
        self.mm_distances = []

    def set(self, data: bytes):
        """
        Set the distance values by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the ToF data.
        """
        # Unpack the byte sequence as 64 Little Endian 16-bit unsigned integers
        # and store them in the mm_distances list
        self.mm_distances = list(struct.unpack(f"<{ToF.tof_num_of_pixels}H", data))

    def __str__(self):
        """
        Returns a string representation of the ToF instance as an 8x8 matrix.
        """
        matrix_representation = ""
        for i in range(0, ToF.tof_num_of_pixels, 8):
            matrix_representation += ' | '.join(map(str, self.mm_distances[i:i + 8])) + '\n'

        return f"ToF distances:\n{matrix_representation}"
