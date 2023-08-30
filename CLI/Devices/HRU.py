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


class HRU(DeviceAbs.DeviceAbs):
    """
    Represents a Heart Rate Unit (HRU) device.
    This device captures both the heart rate (as a float) and the oxygen saturation level (spO2) as an unsigned byte.
    """

    def __init__(self):
        """
        Initialize the HRU device with default values.
        """
        # Initialize the base class
        super().__init__(DeviceAbs.Device_e.HRU)

        # Initialize heart rate as a float with a default value of 0.0
        self.heartRate = 0.0

        # Initialize spO2 (oxygen saturation level) as an unsigned byte with a default value of 0
        self.spO2 = 0

    def set(self, data: bytes):
        """
        Set the HRU attributes by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the HRU data. It should contain a float followed by an unsigned byte.
        """
        # Unpack the byte sequence as a float followed by an unsigned byte
        self.heartRate, self.spO2 = struct.unpack('<fB', data)

    def __str__(self):
        """
        Returns a string representation of the HRU instance.
        """
        return f"Heart Rate: {self.heartRate:.2f} bpm, SpO2: {self.spO2}%"