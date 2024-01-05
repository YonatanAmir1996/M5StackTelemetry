import socket
import struct
import time
import os
import sys

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
import CLI.Assets.CommonMethods as CommonMethods
from CLI.Assets.AbsHandler import AbsHandler


class WifiHandler(AbsHandler):

    host = "0.0.0.0"
    port = 12345

    def __init__(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket = None

        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen()
        print(f"Host: {self.host}:{self.port}")
        self.connect()

    def connect(self):
        if self.client_socket is None:
            print("Trying accept slave connection")
            try:
                self.client_socket, self.addr = self.server_socket.accept()
            except:
                pass

    def disconnect(self):
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None

    def __receive_exact_bytes(self, num_bytes):
        data = b""
        while len(data) < num_bytes:
            chunk = self.client_socket.recv(num_bytes - len(data))
            if not chunk:
                raise ConnectionError("Connection closed or data incomplete")
            data += chunk
        return data

    def write_and_read(self, data):
        """
        Send data to the serial device and wait for response
        :param data: The data in hex format to be sent.
        :return: Bytes received from the device after writing.
        """
        if self.client_socket and CommonMethods.is_valid_hex_array(data):
            # Convert the hex data to bytes.
            data = bytes.fromhex(data)
            num_of_bytes_write = len(data)

            # Continue writing until all data bytes are sent.
            while num_of_bytes_write:
                num_of_bytes_write -= self.client_socket.send(data)

            # Read 4 bytes to determine the number of bytes to read next.
            bytes_to_read = struct.unpack('<I', self.__receive_exact_bytes(4))[0]  # '<I' Little endian representation
            # If there are bytes to read, fetch them; otherwise, return an empty bytes object.
            if bytes_to_read:
                bytes_received = bytes(self.__receive_exact_bytes(bytes_to_read))
            else:
                bytes_received = bytes()
            return bytes_received
