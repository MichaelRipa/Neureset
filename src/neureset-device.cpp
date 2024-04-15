#include "neureset-device.h"
#include <vector>
#include <QDebug>
#include <model.h>
#include "event.h"


NeuresetDevice::NeuresetDevice()
    : deviceOn(true), batteryLevel(100),
      currentScreen(Screen::MainMenu), currentLight(Light::Red), currentDateTime(QDate(1970, 1, 1), QTime(0,0,0))
{}

NeuresetDevice::~NeuresetDevice() {}

void NeuresetDevice::startSession() {
    // Implementation for starting a session
    if (isConnected()) {

        currentSessionStatus = SessionStatus::InProgress;
        currentScreen = Screen::InSession;
        currentSession = new Session(eegHeadset->getNumSites(), currentDateTime);

        // Add event to event queue
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, TIME_TO_COMPUTE_BASELINE_FREQUENCIES);

        //std::vector<double> baseline = session->calculateBaselineAvg(headset);
      //session->applyTreatment(headset);
        Model::Instance()->stateChanged();
  }
  else {
    qDebug("The headset isn't connected");
  }
}

// TODO: Finish
void NeuresetDevice::pauseSession()
{
  currentSessionStatus = SessionStatus::Paused;
  currentSession->setRunning(false);
  Model::Instance()->stateChanged();

  // Does `stateChanged()` suffice for ensuring that the timer begins?
  // How does this function differ during the baselineAvg computation and when applying treatment? (Ignore if done in parent functions)
  qDebug("Unfinished implementation");
}

// TODO: Finish
void NeuresetDevice::userPauseSession() {
  // Implementation for pausing a session when user specifies

  // Some specific actions. 
  pauseSession();  
  qDebug("Unfinished implementation");
}

// TODO: Finish
void NeuresetDevice::connectionLossPauseSession() {
  // Implementation for pausing a session when headset disconnected
  currentLight = Light::Red; // Light flashes red until connection reestablished
  // Some specific actions
  pauseSession();  
  qDebug("Unfinished implementation");
}

void NeuresetDevice::stopSession() {
  // Implementation for stopping a session
  delete currentSession;
  currentSessionStatus = SessionStatus::NotStarted;
  currentScreen = Screen::SessionErased;
  currentLight = Light::Off; // TODO: Call this->connectionStatusChanged() once implementation finished

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

QDateTime NeuresetDevice::getCurrentDateTime() { return currentDateTime; }

void NeuresetDevice::setCurrentDateTime(QDateTime dt) { currentDateTime = dt; }
