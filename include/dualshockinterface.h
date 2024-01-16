#include <thread>
#include <mutex>
#include <fstream>


struct Event {
    long timestamp;
    long timestamp_decimal;
    short type;
    short code;
    int value;
};


class DualShockInterface {
public:
    // Constructor and destructor
    DualShockInterface(const std::string& eventStreamPath);

    // Button property events

    Event BTN_SOUTH;
    Event BTN_EAST;
    Event BTN_WEST;
    Event BTN_NORTH;
    Event BTN_L1;
    Event BTN_R1;
    Event BTN_L2;
    Event BTN_R2;
    Event BTN_SHARE;
    Event BTN_OPTIONS;
    Event BTN_L3;
    Event BTN_R3;
    Event BTN_PS;

    // Joystick property events

    Event ABS_X;
    Event ABS_Y;
    Event ABS_Z;
    Event ABS_RX;
    Event ABS_RY;
    Event ABS_RZ;
    Event ABS_HAT0X;
    Event ABS_HAT0Y;


    // Method to start the C++ loop in a separate thread
    void startListening();

    // Method to stop the C++ loop
    void stop();

private:
    // event stream path
    std::string eventStreamPath;

    // Event stream object
    std::ifstream eventStream;

    std::thread loopThread;  // Thread for the C++ loop
    std::mutex dataMutex;    // Mutex for synchronizing data access
    bool stopRequested;      // Flag to signal the loop to stop

    // Method for the C++ loop
    void loop();
};