import os
import ctypes
from typing import Union


class Event(ctypes.Structure):
    _fields_ = [
        ('timestamp', ctypes.c_long),
        ('timestamp_decimal', ctypes.c_long),
        ('type', ctypes.c_short),
        ('code', ctypes.c_short),
        ('value', ctypes.c_int),
    ]

    def __repr__(self) -> str:
        self.__str__()

    def __str__(self) -> str:
        return 'Event(timestamp={}, timestamp_decimal={}, type={}, code={}, value={})'.format(
            self.timestamp, self.timestamp_decimal, self.type, self.code, self.value
            )

    def __eq__(self, other: "Event") -> bool:
        return self.timestamp == other.timestamp and \
            self.timestamp_decimal == other.timestamp_decimal and \
            self.type == other.type and \
            self.code == other.code and \
            self.value == other.value


class DualshockInterface:

    _NULL_EVENT = Event(0, 0, 0, 0, 0)

    def __init__(self, event_stream_path: str, reset_registers: bool = True) -> None:
        """
        Python wrapper for the DualshockInterface class in C++

        Uses the built library at ./cpp/build/libdualshockinterface.so

        All methods get the previous registered event from the controller.

        Args:
            event_stream_path (str): The path to the event stream file
            reset_registers (bool, optional): If True, resets the event fetched from the event register to None; else same Event.
        """

        if os.path.exists(event_stream_path) is False:
            raise FileNotFoundError('The event stream path does not exist')

        if os.path.exists('./dualshock_controller/cpp/build/libdualshockinterface.so') is False:
            raise FileNotFoundError('The library file does not exist in ./cpp/build/libdualshockinterface.so')

        self.loop_is_running = False
        self._reset_registers = reset_registers

        # Loading the library
        self.lib = ctypes.CDLL('./dualshock_controller/cpp/build/libdualshockinterface.so')

        self.lib.DualshockInterface_new.argtypes = [ctypes.c_char_p]
        self.lib.DualshockInterface_new.restype = ctypes.c_void_p

        # Creating the object and storing it in self.obj
        self.obj = self.lib.DualshockInterface_new(event_stream_path.encode('utf-8'))

    def start_listening(self) -> None:
        self.lib.DualshockInterface_startListening.argtypes = [ctypes.c_void_p]
        self.lib.DualshockInterface_startListening(self.obj)
        self.loop_is_running = True

    def stop(self) -> None:
        self.lib.DualshockInterface_stop.argtypes = [ctypes.c_void_p]
        self.lib.DualshockInterface_stop(self.obj)
        self.loop_is_running = False

    def _get_event(self, event_name: str) -> Union[Event, None]:
        if self.loop_is_running is False:
            raise RuntimeError('The listening loop is not running. Call start_listening() first')

        func = self.lib['DualshockInterface_get' + event_name]
        func.argtypes = [ctypes.c_void_p]
        func.restype = Event

        returned = func(self.obj, self._reset_registers)

        if returned == self._NULL_EVENT:
            return None

        return returned

    def get_btn_cross(self) -> Event:
        return self._get_event('BtnCross')

    def get_btn_circle(self) -> Event:
        return self._get_event('BtnCircle')

    def get_btn_square(self) -> Event:
        return self._get_event('BtnSquare')

    def get_btn_triangle(self) -> Event:
        return self._get_event('BtnTriangle')

    def get_btn_l1(self) -> Event:
        return self._get_event('BtnL1')

    def get_btn_l2(self) -> Event:
        return self._get_event('BtnL2')

    def get_btn_l3(self) -> Event:
        return self._get_event('BtnL3')

    def get_btn_r1(self) -> Event:
        return self._get_event('BtnR1')

    def get_btn_r2(self) -> Event:
        return self._get_event('BtnR2')

    def get_btn_r3(self) -> Event:
        return self._get_event('BtnR3')

    def get_btn_share(self) -> Event:
        return self._get_event('BtnShare')

    def get_btn_options(self) -> Event:
        return self._get_event('BtnOptions')

    def get_btn_ps(self) -> Event:
        return self._get_event('BtnPS')

    def get_axis_left_stick_x(self) -> Event:
        return self._get_event('AxisLeftStickX')

    def get_axis_left_stick_y(self) -> Event:
        return self._get_event('AxisLeftStickY')

    def get_axis_right_stick_x(self) -> Event:
        return self._get_event('AxisRightStickX')

    def get_axis_right_stick_y(self) -> Event:
        return self._get_event('AxisRightStickY')

    def get_axis_l2(self) -> Event:
        return self._get_event('AxisL2')

    def get_axis_r2(self) -> Event:
        return self._get_event('AxisR2')

    def get_axis_dpad_x(self) -> Event:
        return self._get_event('AxisDPadX')

    def get_axis_dpad_y(self) -> Event:
        return self._get_event('AxisDPadY')
