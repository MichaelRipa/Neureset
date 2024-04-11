#include "neureset-device.h"
#include <vector>
#include <QDebug>

NeuresetDevice::NeuresetDevice(EEGHeadset* headset) : batteryLevel(100), connected(true) {
  this->headset = headset;
}

NeuresetDevice::~NeuresetDevice() {}

void NeuresetDevice::startSession() {
  // Implementation for starting a session
  bool connected = headset->isConnected();
  if (connected) {
    sessionStatus = SessionStatus::InProgress; 
    currentScreen = Screen::InSession;
    session = new Session();
    //std::vector<double> baseline = session->calculateBaselineAvg(headset);
  //session->applyTreatment(headset);
  }
  else {
    qDebug("The headset isn't connected");
  }
  // TODO: Connect back to UI
}

void NeuresetDevice::userPauseSession() {
  // Implementation for pausing a session when user specifies
  
}

void NeuresetDevice::connectionLossPauseSession() {
  // Implementation for pausing a session when headset disconnected
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

SessionStatus NeuresetDevice::getSessionStatus() {
  return sessionStatus;
}
