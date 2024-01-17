import ctypes

# Load the C++ library
dualshock_lib = ctypes.CDLL('./libdualshockinterface.so')


# Define the Event structure in Python
class Event(ctypes.Structure):
    _fields_ = [
        ('timestamp', ctypes.c_long),
        ('timestamp_decimal', ctypes.c_long),
        ('type', ctypes.c_short),
        ('code', ctypes.c_short),
        ('value', ctypes.c_int),
    ]


# Define the EventDataHandler class in Python
class EventDataHandler:
    def __init__(self):
        # Constructor declaration
        dualshock_lib.EventDataHandler_new.argtypes = []
        dualshock_lib.EventDataHandler_new.restype = ctypes.c_void_p
        self.obj = dualshock_lib.EventDataHandler()

    def set(self, event):
        dualshock_lib.EventDataHandler_set.argtypes = [ctypes.c_void_p, Event]
        dualshock_lib.EventDataHandler_set(self.obj, event)

    def get(self):
        dualshock_lib.EventDataHandler_get.argtypes = [ctypes.c_void_p]
        dualshock_lib.EventDataHandler_get.restype = Event
        return dualshock_lib.EventDataHandler_get(self.obj)


# Define the DualshockInterface class in Python
class DualshockInterface:
    def __init__(self, event_stream_path):
        dualshock_lib.DualshockInterface_new.argtypes = [ctypes.c_char_p]
        dualshock_lib.DualshockInterface_new.restype = ctypes.c_void_p
        self.obj = dualshock_lib.DualshockInterface_new(event_stream_path.encode('utf-8'))

    def start_listening(self):
        dualshock_lib.DualshockInterface_start_listening.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_start_listening(self.obj)

    def stop(self):
        dualshock_lib.DualshockInterface_stop.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_stop(self.obj)

    def getBtnCross(self):
        dualshock_lib.DualshockInterface_get_event.argtypes = [ctypes.c_void_p]
        dualshock_lib.DualshockInterface_get_event.restype = Event
        return dualshock_lib.DualshockInterface_getBtnCross(self.obj)


# Create an instance of the DualshockInterface class
dualshock = DualshockInterface('/dev/input/event4')

dualshock.start_listening()

while True:
    event = dualshock.getBtnCross()
    print(event.timestamp)
    print(event.timestamp_decimal)
    print(event.type)
    print(event.code)
    print(event.value)
    print('-----------------')
