#include "neureset-device.h"

NeuresetDevice::NeuresetDevice(Headset* headset) : batteryLevel(100), connectionStatus(true) {
  this->headset = headset;
}
NeuresetDevice::~NeuresetDevice() {}

void NeuresetDevice::startSession() {
  // Implementation for starting a session
  bool connected = headset->checkConnection();
  if (connected) {
    sessionStatus = true; 
    session = new Session();
    //eventQueue.addEvent(Event(SessionRunning, ... clock.getTime())); // This event self replicates every time step until session ends or is stopped
    vector<double> baseline = session->calculateBaselineAvg(headset);
session->applyTreatment(headset);
  }
  else {
    cout << "The headset isn't connected" << endl;
  }
}


}

void NeuresetDevice::pauseSession() {
    // Implementation for pausing a session
}

void NeuresetDevice::endSession() {
    // Implementation for ending a session
}

void NeuresetDevice::checkBattery() {
    // Implementation for checking battery level
}

void NeuresetDevice::checkConnection() {
    // Implementation for checking connection status
}

void NeuresetDevice::getSessionStatus() {
  return sessionStatus;
}
