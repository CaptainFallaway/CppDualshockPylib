#include <thread>
#include <mutex>
#include <fstream>

struct EventData {
    long timestamp;
    long timestamp_decimal;
    short type;
    short code;
    int value;
};

class EventDataRegistrar {
    public:
        EventDataRegistrar();
        void set(EventData& eventData);
        EventData get();
    private:
        EventData eventData;
        std::mutex mutex;
};

class DualshockInterface {
public:
    // Constructor and destructor
    DualshockInterface(const std::string& eventStreamPath);

    ~DualshockInterface();

    // EventData data handlers

    EventDataRegistrar btnCross;
    EventDataRegistrar btnCircle;
    EventDataRegistrar btnSquare;
    EventDataRegistrar btnTriangle;
    EventDataRegistrar btnL1;
    EventDataRegistrar btnL2;
    EventDataRegistrar btnL3;
    EventDataRegistrar btnR1;
    EventDataRegistrar btnR2;
    EventDataRegistrar btnR3;
    EventDataRegistrar btnShare;
    EventDataRegistrar btnOptions;
    EventDataRegistrar btnPS;

    EventDataRegistrar axisLeftStickX;
    EventDataRegistrar axisLeftStickY;
    EventDataRegistrar axisRightStickX;
    EventDataRegistrar axisRightStickY;
    EventDataRegistrar axisL2;
    EventDataRegistrar axisR2;
    EventDataRegistrar axisDPadX;
    EventDataRegistrar axisDPadY;

    // Method to start the C++ loop in a separate thread
    void startListening();

    // Method to stop the C++ loop
    void stop();
private:
    // EventData stream path
    const std::string eventStreamPath;

    // EventData stream object
    std::ifstream eventStream;

    std::thread loopThread;  // Thread for the C++ loop
    std::mutex dataMutex;    // Mutex for synchronizing data access
    bool stopRequested;      // Flag to signal the loop to stop

    // Method for the C++ loop
    void loop();

    void handleKeyEvent(EventData& event);

    void handleAxisEvent(EventData& event);
};