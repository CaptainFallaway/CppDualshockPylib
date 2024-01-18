# Testing

from dualshock_controller import DualshockInterface, Event  # noqa: F401

interface = DualshockInterface("/dev/input/event4")

interface.start_listening()

print("Started listening")

funcs = list(
    filter(
        lambda x: x.startswith("get_"),
        interface.__dir__()
    )
)

while True:
    for func in funcs:
        event = getattr(interface, func)()
        if event is not None:
            print(event)
            print("\n---------------------------------\n")
