# CppDualshockPylib

## Compile the cpp library

I am expecting you to have sshed into a EV3 robot with the EV3dev OS and cloned / downloaded the project.

1. cd into the cpp directory inside of the dualshock_controller folder
2. run the build script with ./build.sh

## Example of use

```py
from dualshock_controller import DualshockInterface, Event

def main():
  controller = DualshockInterface()
  controller.start_listening()

  while True:
    # controller.get_btn_cross() returns a ctypes event object with the properties: 
    # timestamp, timestamp decimal, type, code, value
    # You should usually only care about the value property but i choose to return the whole event.
    # I should also mention if no event has been registered the return value will be None.

    btn_cross = controller.get_btn_cross()
    ps_btn = controller.get_btn_ps()
    r1_axis = controller.get_axis_right_stick_x()

    if r1_axis is not None:
      print("Right stick x value: ", r1_axis.value)

    if ps_btn is None:
      continue
    elif btn_cross.value == 1:
      print("Cross Pressed")
    elif btn_cross.value == 0:
      print("Cross Released")

    if ps_btn is None:
      continue
    elif ps_btn.value == 1:
      break

  # Reccomended to always stop the listener in the end of execution or else you will have a loose thread.
  controller.stop()

if __name__ == "__main__":
  main()
```
