from dualshock_controller import DualshockInterface, Event  # noqa: F401

interface = DualshockInterface("/dev/input/event4")

interface.start_listening()

while True:
    event = interface.get_btn_cross()

    if event is not None:
        print(event)
