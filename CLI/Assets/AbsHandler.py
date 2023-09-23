import os
import sys
import abc

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)


class AbsHandler:

    @abc.abstractmethod
    def connect(self):
        """
        Attempts to establish a connection.
        :return: Boolean indicating the status of the connection.
        """
        pass

    @abc.abstractmethod
    def disconnect(self):
        """Close connection."""
        pass

    @abc.abstractmethod
    def write_and_read(self, data):
        """
        Send data to the serial device and wait for response
        :param data: The data in hex format to be sent.
        :return: Bytes received from the device after writing.
        """
        pass
