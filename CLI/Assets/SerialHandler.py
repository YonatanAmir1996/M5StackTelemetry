import serial.tools.list_ports
import serial
import os
import sys
root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
import CLI.Assets.CommonMethods as CommonMethods


class SerialHandler:
    # Manufacture vid & pid
    pid = 0x1001
    vid = 0x303a
    default_baudrate = 115200

    def __init__(self, baudrate=default_baudrate):
        """
        Serial handler with M5Stack
        :param baudrate:
        """
        self.__comport = None
        for port in serial.tools.list_ports.comports():
            if (self.pid == port.pid) and (self.vid == port.vid):
                self.__comport = port.name
        self.__serial = serial.Serial(timeout=None)
        self.__serial.baudrate = baudrate
        self.__serial.port = self.__comport
        self.__buffer = []
        self.connect()

    def connect(self):
        """
        connect to serial
        :return: if connected to the device
        """
        if self.__comport is None:
            ret_val = False
        else:
            self.__serial.open()
            ret_val = self.__serial.is_open
            print(f"connected to device {ret_val}")
        return ret_val

    def disconnect(self):
        self.__serial.close()

    def write(self, data):
        if self.__serial.is_open and CommonMethods.is_valid_hex_array(data):
            # print(data, bytes.fromhex(data))
            # Thread lock to prevent from python instance read bytes
            self.__serial.write(bytes.fromhex(data))
            while self.__serial.in_waiting < 4:
                pass
            bytes_to_read = int.from_bytes(self.__serial.read(4), byteorder='little')
            self.__serial.flush()
            # print(bytes_to_read)
            while self.__serial.in_waiting != bytes_to_read:
                pass
            bytes_received = self.__serial.read(self.__serial.in_waiting)
            return bytes_received