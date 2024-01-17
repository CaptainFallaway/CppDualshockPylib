# Nothing fancy since i'm just doing a quick build on a ev3dev robot.

mkdir -p build
g++ -Wall -shared -fPIC -Iinclude -o build/libdualshockinterface.so src/dualshockinterface.cpp