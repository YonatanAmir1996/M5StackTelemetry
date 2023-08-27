import enum
import struct
from SerialHandler import SerialHandler


class Commands(enum.IntEnum):
    COMMAND_RESCAN_SENSORS = 0
    COMMAND_RUN_SENSORS = 1
    COMMAND_AVAILABLE_DEVICES = 2


class CommandHandler:
    invalid_pb_hub_port = 0xFF
    def __init__(self):
        self.__handler = None
        for handler in [SerialHandler()]:
            if handler.connect():
                self.__handler = handler

        if self.__handler is None:
            raise ConnectionError("Couldn't connect to M5Stack")

    def command_run_sensors(self, sensors_bmp):
        """
        :param   sensors_bmp: sensors bitmap according to DeviceName_e enum
        :return:
        """
        if not isinstance(sensors_bmp, int):
            raise TypeError("Please use int type only !")
        self.send_command(Commands.COMMAND_RUN_SENSORS, sensors_bmp)

    def send_command(self, command : Commands, *args, **kwargs):
        """
        Write command in serial/wifi
        :param command: command name
        :param args:
        :param kwargs:
        :return:
        """
        # Writes how many bytes should be read -> (command) + (4*args) bytes
        total_bytes = 4 + (len(args) << 2)
        self.__handler.write(f"{total_bytes:08X}".upper())

        # 4 bytes for command name
        raw_data = struct.pack(">I", command.value)

        # Convert and append each argument
        for arg in args:
            raw_data += struct.pack(">I", arg)
        self.__handler.write(raw_data.hex().upper())


CommandHandler().command_run_sensors(15)





