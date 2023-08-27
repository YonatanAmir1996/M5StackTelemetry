import serial.tools.list_ports
import serial
import threading
import copy
import time
import CommonMethods


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
        self.__thread = threading.Thread(target=self.__run)
        self.__can_run = True
        self.__serial = serial.Serial()
        self.__serial.baudrate = baudrate
        self.__serial.port = self.__comport
        self.__buffer = []

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
                self.__thread.start()
        return ret_val

    def __run(self):
        while self.__can_run:
            pending_bytes = self.__serial.in_waiting
            while pending_bytes > 0:  # While there are bytes available
                byte_received = self.__serial.read(pending_bytes)
                self.__buffer.append(byte_received.decode('utf-8'))
            time.sleep(0.1)

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

    def is_alive(self):
        return self.__can_run

    def write(self, data):
        if self.__serial.is_open and CommonMethods.is_valid_hex_array(data):
            print(data, bytes.fromhex(data))
            # Thread lock to prevent from python instance read bytes
            with threading.Lock():
                self.__serial.write(bytes.fromhex(data))
                while self.__serial.in_waiting:
                    time.sleep(0.1)