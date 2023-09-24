import enum
import struct
import os
import sys

root_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../")
sys.path.append(root_path)
from CLI.Assets.SerialHandler import SerialHandler


class Commands_e(enum.IntEnum):
    """
    Supported commands. Commands must be aligned Commands_e of main/SharedDefines.h
    """
    COMMAND_RESCAN_SENSORS = 0
    COMMAND_RUN_SENSORS = 1
    COMMAND_SET_RGB = 2
    COMMAND_SET_MOTOR = 3
    COMMAND_SET_SPEAKER = 4


class PbHubPortAddr_e(enum.IntEnum):
    PORT_0 = 0x40
    PORT_1 = 0x50
    PORT_2 = 0x60
    PORT_3 = 0x70
    PORT_4 = 0x80
    PORT_5 = 0xA0


class CommandHandler:
    invalid_pb_hub_port = 0xFF

    def __init__(self):
        # TODO: need to Create WIFI Handler
        self.__handler = SerialHandler()

        if self.__handler is None:
            raise ConnectionError("Couldn't connect to M5Stack")

    def disconnect(self):
        self.__handler.disconnect()

    def send_command(self, command: Commands_e, *args, **kwargs):
        """
        Write command in serial/wifi
        :param command: command name
        :param args:
        :param kwargs:
        :return:
        """
        # Writes how many bytes should be read -> (command) + (4*args) bytes
        total_bytes = 4 + (len(args) << 2)
        # 4 bytes for command name
        raw_data = struct.pack(">I", command.value)

        # Convert and append each argument
        for arg in args:
            raw_data += struct.pack(">I", arg)

        return self.__handler.write_and_read(f"{total_bytes:08X}".upper() + raw_data.hex().upper())
