import ctypes
from time import sleep

dualshock_lib = ctypes.CDLL('./build/libdualshockinterface.so')


class Event(ctypes.Structure):
    _fields_ = [
        ('timestamp', ctypes.c_long),
        ('timestamp_decimal', ctypes.c_long),
        ('type', ctypes.c_short),
        ('code', ctypes.c_short),
        ('value', ctypes.c_int),
    ]


class DualshockInterface:
    def __init__(self, event_stream_path):
        dualshock_lib.DualshockInterface_new.argtypes = [ctypes.c_char_p]
        dualshock_lib.DualshockInterface_new.restype = ctypes.c_void_p
        self.obj = dualshock_lib.DualshockInterface_new(event_stream_path.encode('utf-8'))

    def start_listening(self):
        dualshock_lib.DualshockInterface_startListening.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_startListening(self.obj)

    def stop(self):
        dualshock_lib.DualshockInterface_stop.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_stop(self.obj)

    def getBtnCross(self) -> Event:
        dualshock_lib.DualshockInterface_getBtnCross.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_getBtnCross.restype = Event
        return dualshock_lib.DualshockInterface_getBtnCross(self.obj)


dualshock = DualshockInterface('/dev/input/event4')

dualshock.start_listening()

while True:
    cross = dualshock.getBtnCross()
    if cross.value == 1:
        print('Cross pressed')
    elif cross.value == 0:
        print('Cross released')