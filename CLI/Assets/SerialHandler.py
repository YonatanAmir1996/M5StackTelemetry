import serial.tools.list_ports
import serial
import os
import sys
import time

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
import CLI.Assets.CommonMethods as CommonMethods
from CLI.Assets.AbsHandler import AbsHandler


class SerialHandler(AbsHandler):
    # Define constants for the USB device's vendor and product ID.
    pid = 0x1001
    vid = 0x303a
    default_baudrate = 115200

    def __init__(self, baudrate=default_baudrate):
        """
        Initializes the SerialHandler object to communicate with the M5Stack device.
        :param baudrate: Baud rate for serial communication. Defaults to 115200.
        """

        # Initially set the communication port to None.
        self.__comport = None

        # Iterate over available serial ports to identify the port associated with the desired device.
        for port in serial.tools.list_ports.comports():
            if (self.pid == port.pid) and (self.vid == port.vid):
                if os.name == 'posix':
                    self.__comport = os.path.join(r"/dev", port.name)
                else:
                    self.__comport = port.name

        # Configure the serial connection using the identified port and specified baud rate.
        self.__serial = serial.Serial()
        self.__serial.baudrate = baudrate
        self.__serial.port = self.__comport
        self.__timeout = 30
        # Try to establish the serial connection.
        self.connect()

    def connect(self):
        # If no matching COM port is found, return False.
        if self.__comport is None:
            ret_val = False
        else:
            # Attempt to open the serial connection.
            self.__serial.open()
            ret_val = self.__serial.is_open  # Check if the connection is open.
            print(f"connected to device via serial: {ret_val}")
        return ret_val

    def disconnect(self):
        """Close the serial connection."""
        self.__serial.close()

    def write_and_read(self, data):
        # Check if the serial connection is active and if the provided data is in a valid hex format.
        if self.__serial.is_open and CommonMethods.is_valid_hex_array(data):
            # Convert the hex data to bytes.
            data = bytes.fromhex(data)
            num_of_bytes_write = len(data)

            # Continue writing until all data bytes are sent.
            while num_of_bytes_write:
                num_of_bytes_write -= self.__serial.write(data)

            # Wait for at least 4 bytes to be available in the input buffer.
            while self.__serial.in_waiting < 4:
                time.sleep(0.01)
            # Read 4 bytes to determine the number of bytes to read next.
            bytes_to_read = int.from_bytes(self.__serial.read(4), byteorder='little')
            bytes_received = bytes()
            while bytes_to_read:
                if self.__serial.in_waiting:
                    temp_packet = self.__serial.read(min(bytes_to_read, self.__serial.in_waiting))
                    bytes_received += temp_packet
                    bytes_to_read -= len(temp_packet)
                else:
                    time.sleep(0.01)  # Wait a bit for more data to arrive
            return bytes_received
