# Import necessary modules
import os
import sys
import struct

# Determine the root path and append it to the system path
# This step ensures that the program can import modules from the parent directory
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

# Import the DeviceAbs module from the CLI.Devices package
import CLI.Devices.DeviceAbs as DeviceAbs


class Fsr(DeviceAbs.DeviceAbs):
    """
    Represents a Force Sensing Resistor (FSR) device.
    """

    def __init__(self, fsr_type: DeviceAbs.Device_e):
        """
        Initialize the FSR device.
        """
        # Initialize the base class
        super().__init__(fsr_type)

        # Initialize the fsrValue attribute which will hold the FSR reading
        self.fsrValue = 0

    def set(self, data: bytes):
        """
        Set the FSR value by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the FSR data.
        """
        # Unpack the byte sequence as a Little Endian 16-bit unsigned integer
        # and set it as the FSR value
        self.fsrValue = struct.unpack('<H', data)[0]

    def __str__(self):
        return f"FSR value: {self.fsrValue}"
