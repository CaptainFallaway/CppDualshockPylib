// include dualshockinterface.h

#include "dualshockinterface.h"

DualShockInterface::DualShockInterface(const std::string& eventStreamPath) {
    this.eventStreamPath = eventStreamPath;
}

void DualShockInterface::startListening() {
    // Start the C++ loop in a separate thread
    loopThread = std::thread(&DualShockInterface::loop, this);
}

void DualShockInterface::stop() {
    // Signal the loop to stop
    stopRequested = true;

    // Wait for the loop to finish
    loopThread.join();
}

void DualShockInterface::loop() {
    // Loop until stop is requested
    while (!stopRequested) {
        
    }
}
