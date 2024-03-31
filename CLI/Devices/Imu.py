import os
import sys
import struct

# Set up the path for importing modules
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)

# Import the DeviceAbs from CLI.Devices module
import CLI.Devices.DeviceAbs as DeviceAbs

class Imu(DeviceAbs.DeviceAbs):
    """
    Represents an Inertial Measurement Unit (IMU) device.
    """

    class GyroData:
        """
        Represents data from a gyroscope.
        """
        def __init__(self, x:int = 0, y:int = 0, z:int = 0):
            self.x = x
            self.y = y
            self.z = z

        def __str__(self):
            return f"GyroData(x={self.x:4.2f}, y={self.y:4.2f}, z={self.z:4.2f})"

    class AccelData:
        """
        Represents data from an accelerometer.
        """
        def __init__(self, x:int = 0, y:int = 0, z:int = 0):
            self.x = x
            self.y = y
            self.z = z

        def __str__(self):
            return f"AccelData(x={self.x:4.2f}, y={self.y:4.2f}, z={self.z:4.2f})"

    def __init__(self):
        """
        Initialize the IMU device.
        """
        # Initialize the base class
        super().__init__(DeviceAbs.Device_e.IMU)

        # Initialize the gyroscope and accelerometer data objects
        self.accel_data = self.AccelData()
        self.gyro_data = self.GyroData()

    def set(self, data:bytes):
        """
        Set the IMU data by unpacking a given byte sequence.

        Args:
            data (bytes): The byte sequence containing the gyro and accel data.
        """
        # Unpack the byte sequence.
        # Note: the gyro data appears first in the byte sequence.
        self.gyro_data.x, self.gyro_data.y, self.gyro_data.z, \
        self.accel_data.x, self.accel_data.y, self.accel_data.z = struct.unpack('<6f', data)

    def __str__(self):
        return f"Imu(Gyro={self.gyro_data}, Accel={self.accel_data})"