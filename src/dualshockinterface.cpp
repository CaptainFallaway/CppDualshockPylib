#include "dualshockinterface.h"
#include "constants.h"

// Initialize the EventDataRegistrar with an empty EventData struct and a mutex used for thread safety when setting and getting the data
EventDataRegistrar::EventDataRegistrar() : eventData(), mutex() {}

void EventDataRegistrar::set(EventData& eventData) {
    std::lock_guard<std::mutex> lock(mutex);
    this->eventData = eventData;
}

EventData EventDataRegistrar::get() {
    std::lock_guard<std::mutex> lock(mutex);
    return eventData;
}

// Initialize the DualshockInterface
DualshockInterface::DualshockInterface(const std::string& eventStreamPath) : eventStreamPath(eventStreamPath), stopRequested(false) {};

DualshockInterface::~DualshockInterface() {
    stop();
}

void DualshockInterface::startListening() {
    loopThread = std::thread(&DualshockInterface::loop, this);
}

void DualshockInterface::stop() {
    stopRequested = true;
    eventStream.close();

    if (loopThread.joinable()) 
        loopThread.join();
}

void DualshockInterface::loop() {
    // The loop that runs in a separate thread

    eventStream.open(eventStreamPath, std::ios::in | std::ios::binary);  // Open the event stream

    if (!eventStream.is_open() || eventStream.fail()) {
        throw std::runtime_error("Event stream failed to open!\nSee if controller has disconnected or changed event stream path.");
        return;
    }

    // Initialize a EventData so it can be mutated in the loop
    EventData event;

    // Loop until stop is requested
    while (!stopRequested) {
        eventStream.read(reinterpret_cast<char*>(&event), sizeof(EventData));

        switch (event.type)
        {
            case (EV_KEY):
                handleKeyEvent(event);
                break;
            case (EV_ABS):
                handleAxisEvent(event);
                break;
            default:
                break;
        }
    }
}

void DualshockInterface::handleKeyEvent(EventData& event) {
    switch (event.code)
    {
        case (BTN_CROSS):
            btnCross.set(event);
            break;
        case (BTN_CIRCLE):
            btnCircle.set(event);
            break;
        case (BTN_TRIANGLE):
            btnTriangle.set(event);
            break;
        case (BTN_SQUARE):
            btnSquare.set(event);
            break;
        case (BTN_L1):
            btnL1.set(event);
            break;
        case (BTN_R1):
            btnR1.set(event);
            break;
        case (BTN_L2):
            btnL2.set(event);
            break;
        case (BTN_R2):
            btnR2.set(event);
            break;
        case (BTN_SHARE):
            btnShare.set(event);
            break;
        case (BTN_OPTIONS):
            btnOptions.set(event);
            break;
        case (BTN_PS):
            btnPS.set(event);
            break;
        case (BTN_L3):
            btnL3.set(event);
            break;
        case (BTN_R3):
            btnR3.set(event);
            break;
        default:
            break;
    }
}

void DualshockInterface::handleAxisEvent(EventData& event) {
    switch (event.code)
    {
        case (ABS_X):
            axisLeftStickX.set(event);
            break;
        case (ABS_Y):
            axisLeftStickY.set(event);
            break;
        case (ABS_Z):
            axisL2.set(event);
            break;
        case (ABS_RX):
            axisRightStickX.set(event);
            break;
        case (ABS_RY):
            axisRightStickY.set(event);
            break;
        case (ABS_RZ):
            axisR2.set(event);
            break;
        case (ABS_HAT0X):
            axisDPadX.set(event);
            break;
        case (ABS_HAT0Y):
            axisDPadY.set(event);
            break;
        default:
            break;
    }
}


// C interface for the DualshockInterface class to be used in Python with ctypes
extern "C" {
    DualshockInterface* DualshockInterface_new(const char* eventStreamPath) {
        return new DualshockInterface(eventStreamPath);
    }

    void DualshockInterface_delete(DualshockInterface* dualshockInterface) {
        delete dualshockInterface;
    }

    void DualshockInterface_startListening(DualshockInterface* dualshockInterface) {
        dualshockInterface->startListening();
    }

    void DualshockInterface_stop(DualshockInterface* dualshockInterface) {
        dualshockInterface->stop();
    }

    EventData DualshockInterface_getBtnCross(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnCross.get();
    }

    EventData DualshockInterface_getBtnCircle(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnCircle.get();
    }

    EventData DualshockInterface_getBtnSquare(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnSquare.get();
    }

    EventData DualshockInterface_getBtnTriangle(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnTriangle.get();
    }

    EventData DualshockInterface_getBtnL1(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnL1.get();
    }

    EventData DualshockInterface_getBtnL2(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnL2.get();
    }

    EventData DualshockInterface_getBtnL3(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnL3.get();
    }

    EventData DualshockInterface_getBtnR1(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnR1.get();
    }

    EventData DualshockInterface_getBtnR2(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnR2.get();
    }

    EventData DualshockInterface_getBtnR3(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnR3.get();
    }

    EventData DualshockInterface_getBtnShare(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnShare.get();
    }

    EventData DualshockInterface_getBtnOptions(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnOptions.get();
    }

    EventData DualshockInterface_getBtnPS(DualshockInterface* dualshockInterface) {
        return dualshockInterface->btnPS.get();
    }

    EventData DualshockInterface_getAxisLeftStickX(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisLeftStickX.get();
    }

    EventData DualshockInterface_getAxisLeftStickY(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisLeftStickY.get();
    }

    EventData DualshockInterface_getAxisRightStickX(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisRightStickX.get();
    }

    EventData DualshockInterface_getAxisRightStickY(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisRightStickY.get();
    }

    EventData DualshockInterface_getAxisL2(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisL2.get();
    }

    EventData DualshockInterface_getAxisR2(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisR2.get();
    }

    EventData DualshockInterface_getAxisDPadX(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisDPadX.get();
    }

    EventData DualshockInterface_getAxisDPadY(DualshockInterface* dualshockInterface) {
        return dualshockInterface->axisDPadY.get();
    }

    void DualshockInterface_delete (DualshockInterface* dualshockInterface) {
        delete dualshockInterface;
    }
}