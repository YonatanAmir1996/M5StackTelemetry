import enum


class Device_e(enum.IntEnum):
    IMU = 0
    HRU = 1
    AMG833 = 2
    TOF = 3
    FSR = 4


class DeviceAbs:

    def __init__(self, device_name : Device_e):
        self.device_name = device_name

    def set(self, data):
        """
        set sensor values
        :return:
        """
        pass