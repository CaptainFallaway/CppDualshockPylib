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


class EventDataHandler {
    public:
        EventDataHandler();
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

    // Methods to get the "newest" button events from the EventData stream

    EventData getBtnCross();
    EventData getBtnCircle();
    EventData getBtnSquare();
    EventData getBtnTriangle();
    EventData getBtnL1();
    EventData getBtnL2();
    EventData getBtnL3();
    EventData getBtnR1();
    EventData getBtnR2();
    EventData getBtnR3();
    EventData getBtnShare();
    EventData getBtnOptions();
    EventData getBtnPS();

    // Methods to get the "newest" axis events from the EventData stream

    EventData getAxisLeftStickX();
    EventData getAxisLeftStickY();
    EventData getAxisRightStickX();
    EventData getAxisRightStickY();
    EventData getAxisL2();
    EventData getAxisR2();
    EventData getAxisDPadX();
    EventData getAxisDPadY();

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

    // EventData data handlers

    EventDataHandler btnCross;
    EventDataHandler btnCircle;
    EventDataHandler btnSquare;
    EventDataHandler btnTriangle;
    EventDataHandler btnL1;
    EventDataHandler btnL2;
    EventDataHandler btnL3;
    EventDataHandler btnR1;
    EventDataHandler btnR2;
    EventDataHandler btnR3;
    EventDataHandler btnShare;
    EventDataHandler btnOptions;
    EventDataHandler btnPS;

    EventDataHandler axisLeftStickX;
    EventDataHandler axisLeftStickY;
    EventDataHandler axisRightStickX;
    EventDataHandler axisRightStickY;
    EventDataHandler axisL2;
    EventDataHandler axisR2;
    EventDataHandler axisDPadX;
    EventDataHandler axisDPadY;

    // Method for the C++ loop
    void loop();

    void handleKeyEvent(EventData& event);

    void handleAxisEvent(EventData& event);
};