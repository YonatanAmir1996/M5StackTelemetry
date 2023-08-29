import serial.tools.list_ports
import serial
import threading
import copy
import time
import CommonMethods
import struct

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
            if ret_val:
                self.__can_run = True
        return ret_val

    def disconnect(self):
        self.__can_run = False
        self.__serial.close()

    def dump_buffer(self, print_buffer=False):
        """
        Dumps raw data from Serial
        :return:
        """
        temp_buffer = []
        if self.__buffer:
            temp_buffer = copy.deepcopy(self.__buffer)
            self.__buffer = []
            if print_buffer:
                print(f"{''.join(temp_buffer)}")
        return temp_buffer

    def write(self, data):
        if self.__serial.is_open and CommonMethods.is_valid_hex_array(data):
            # print(data, bytes.fromhex(data))
            # Thread lock to prevent from python instance read bytes
            self.__serial.write(bytes.fromhex(data))
            while self.__serial.in_waiting < 4:
                pass
            bytes_to_read = int.from_bytes(self.__serial.read(4), byteorder='little')
            print(bytes_to_read)
            while self.__serial.in_waiting != bytes_to_read:
                pass
            bytes_received = self.__serial.read(bytes_to_read)
            print(bytes_received)