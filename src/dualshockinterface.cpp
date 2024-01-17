#include "dualshockinterface.h"


EventDataHandler::EventDataHandler() : eventData(), mutex() {}


void EventDataHandler::set(EventData& eventData) {
    std::lock_guard<std::mutex> lock(mutex);
    this->eventData = eventData;
}


EventData EventDataHandler::get() {
    std::lock_guard<std::mutex> lock(mutex);
    return eventData;
}


DualshockInterface::DualshockInterface(const std::string& eventStreamPath) : eventStreamPath(eventStreamPath), stopRequested(false) {};


DualshockInterface::~DualshockInterface() {
    // Stop the loop if it is running
    if (loopThread.joinable()) {
        stop();
    }
}


void DualshockInterface::startListening() {
    eventStream.open(eventStreamPath, std::ios::in | std::ios::binary);

    // Start the C++ loop in a separate thread
    loopThread = std::thread(&DualshockInterface::loop, this);
}


void DualshockInterface::stop() {
    // Signal the loop to stop
    stopRequested = true;

    // Wait for the loop to finish
    loopThread.join();
}


void DualshockInterface::loop() {
    if (!eventStream.is_open()) {
        throw std::runtime_error("Event stream not open");
        return;
    }

    EventData event;

    // Loop until stop is requested
    while (!stopRequested) {
        eventStream.read(reinterpret_cast<char*>(&event), sizeof(EventData));

        switch (event.type)
        {
            case (1):
                handleKeyEvent(event);
                break;
            case (3):
                handleAxisEvent(event);
                break;
            default:
                break;
        }
    }
}


void DualshockInterface::handleAxisEvent(EventData& event) {
    switch (event.code)
    {
        case (0):
            axisLeftStickX.set(event);
            break;
        case (1):
            axisLeftStickY.set(event);
            break;
        case (2):
            axisL2.set(event);
            break;
        case (3):
            axisRightStickX.set(event);
            break;
        case (4):
            axisRightStickY.set(event);
            break;
        case (5):
            axisR2.set(event);
            break;
        case (16):
            axisDPadX.set(event);
            break;
        case (17):
            axisDPadY.set(event);
            break;
        default:
            break;
    }
}


void DualshockInterface::handleKeyEvent(EventData& event) {
    switch (event.code)
    {
        case (304):
            btnCross.set(event);
            break;
        case (305):
            btnCircle.set(event);
            break;
        case (307):
            btnTriangle.set(event);
            break;
        case (308):
            btnSquare.set(event);
            break;
        case (310):
            btnL1.set(event);
            break;
        case (311):
            btnR1.set(event);
            break;
        case (312):
            btnL2.set(event);
            break;
        case (313):
            btnR2.set(event);
            break;
        case (314):
            btnShare.set(event);
            break;
        case (315):
            btnOptions.set(event);
            break;
        case (316):
            btnPS.set(event);
            break;
        case (317):
            btnL3.set(event);
            break;
        case (318):
            btnR3.set(event);
            break;
        default:
            break;
    }
}