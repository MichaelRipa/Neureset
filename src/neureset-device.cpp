#include "neureset-device.h"
#include <vector>
#include <QDebug>
#include <model.h>
#include "event.h"

NeuresetDevice::NeuresetDevice()
    : deviceOn(true), batteryLevel(100),
      currentScreen(Screen::MainMenu), currentLight(Light::Red)
{}

NeuresetDevice::~NeuresetDevice() {}

void NeuresetDevice::startSession() {
    // Implementation for starting a session
    if (isConnected()) {

        currentSessionStatus = SessionStatus::InProgress;
        currentScreen = Screen::InSession;
        currentSession = new Session(eegHeadset->getNumSites());


        // Add event to event queue
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, 5000);

        //std::vector<double> baseline = session->calculateBaselineAvg(headset);
      //session->applyTreatment(headset);
        Model::Instance()->stateChanged();
  }
  else {
    qDebug("The headset isn't connected");
  }
}

void NeuresetDevice::pauseSession()
{

}

void NeuresetDevice::userPauseSession() {
  // Implementation for pausing a session when user specifies
  
}

void NeuresetDevice::connectionLossPauseSession() {
  // Implementation for pausing a session when headset disconnected
}

void NeuresetDevice::stopSession() {
  // Implementation for stopping a session
  delete currentSession;
  currentSessionStatus = SessionStatus::NotStarted;
  currentScreen = Screen::SessionErased;
  currentLight = Light::Off;

  Model::Instance()->stateChanged();
}

void NeuresetDevice::calculateBaselineAverages()
{
    qDebug("Baseline averages totally calculated.");
}

void NeuresetDevice::setEEGHeadset(EEGHeadset *eegHeadset)
{
    this->eegHeadset = eegHeadset;
}

// TODO - finish implementing
void NeuresetDevice::connectionStatusChanged()
{
    if (!isConnected())
        currentLight = Light::Red;
    else
        currentLight = Light::Blue;


}

Session* NeuresetDevice::getCurrentSession() { return currentSession; }

int NeuresetDevice::getBatteryLevel() { return batteryLevel; }

NeuresetDevice::Light NeuresetDevice::getCurrentLight() { return currentLight; }

NeuresetDevice::SessionStatus NeuresetDevice::getCurrentSessionStatus() {return currentSessionStatus; }

NeuresetDevice::Screen NeuresetDevice::getCurrentScreen() { return currentScreen; }

bool NeuresetDevice::isConnected() { return eegHeadset->isConnected(); }

bool NeuresetDevice::isOn() { return deviceOn; }


