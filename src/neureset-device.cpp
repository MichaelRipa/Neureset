#include "neureset-device.h"
#include <vector>
#include <QDebug>
#include <model.h>
#include "event.h"


NeuresetDevice::NeuresetDevice()
    : deviceOn(true), batteryLevel(100),
      currentScreen(Screen::MainMenu), currentConnectionStatus(ConnectionStatus::ContactLost),
      currentDateTime(QDate(1970, 1, 1), QTime(0,0,0)), currentSessionStatus(SessionStatus::NotStarted)
{}

NeuresetDevice::~NeuresetDevice() {
  delete pc;
  clearAllSessions();
  if (currentSession) {
    delete currentSession;
  }
}

void NeuresetDevice::startSession() {
    // Implementation for starting a session
    if (isConnected()) {

        currentSessionStatus = SessionStatus::InProgress;
        currentScreen = Screen::InSession;

        currentSession = new Session(eegHeadset->getNumSites(), currentDateTime);
        currentSession->startTimer();
        currentSession->setStage(Session::Stage::computePreTreatmentBaselines);

        runCurrentSessionStage();

        Model::Instance()->stateChanged();
  }
  else {
    qDebug("The headset isn't connected");
  }
}

// Goes to the next stage of the current session treatment. Only called once the previous stage is done
// or if restarting a stage due to session being paused.
void NeuresetDevice::runCurrentSessionStage() {
    // Sanity check (since method should only be called under these conditions)
    if (!(currentScreen == Screen::InSession && eegHeadset->isConnected()))
        return;

    currentSessionStatus = SessionStatus::InProgress;

    // Add running of current stage to event queue. The callbacks called when ready, and they also handle
    // changing the session stage (so not done here).
    if(currentSession->getStage() == Session::Stage::computePreTreatmentBaselines) {
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, TIME_TO_COMPUTE_FREQUENCY);
    }
    // If at this stage, treatment is applied to the next site
    else if (currentSession->getStage() == Session::Stage::ApplyTreatmentToSites) {
        // Compute dominant frequencies event. Once done, it will create further events for adding treatment.
        Model::Instance()->addToEventQueue(Event::EventType::CalculateFrequencyAtCurrentSite, TIME_TO_COMPUTE_FREQUENCY);
    }
    else if (currentSession->getStage() == Session::Stage::computePostTreatmentBaselines) {
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, TIME_TO_COMPUTE_FREQUENCY);
    }
}


void NeuresetDevice::userPauseSession() {
  // Implementation for pausing a session when user specifies
    currentSession->pauseTimer();
    currentSessionStatus = SessionStatus::UserPausedSession;
    updateConnectionStatus();

    Model::Instance()->addToEventQueue(Event::EventType::UserPausedSession, SESSION_PAUSED_TIMEOUT);
}

void NeuresetDevice::userUnpauseSession()
{
    if (eegHeadset->isConnected()) {
        currentSessionStatus = SessionStatus::InProgress;
        currentSession->startTimer();
    }
    // Case where session unpaused but connection lost
    else {
        currentSessionStatus = SessionStatus::ConnectionLossPausedSession;
    }
    updateConnectionStatus();
}


void NeuresetDevice::connectionLossPauseSession() {
    currentSession->pauseTimer();
    currentSessionStatus = SessionStatus::ConnectionLossPausedSession;
    updateConnectionStatus();

    Model::Instance()->addToEventQueue(Event::EventType::connectionLossPausedSession, SESSION_PAUSED_TIMEOUT);
    Model::Instance()->stateChanged();

}

void NeuresetDevice::stopSession() {
  // Implementation for stopping a session
  delete currentSession;
  currentSessionStatus = SessionStatus::UserStoppedSession;
  currentScreen = Screen::SessionErased;
  updateConnectionStatus();

  Model::Instance()->stateChanged();
}

void NeuresetDevice::clearAllSessions() {
  for (Session* session : allSessions) {
    delete session;
  }
  allSessions.clear();
}

void NeuresetDevice::uploadAllSessions() {
  pc->uploadData(allSessions);
  // Once data is uploaded, can clear list to avoid duplicate uploads
  clearAllSessions();
}

void NeuresetDevice::updateConnectionStatus()
{
    if (!deviceOn)
        currentConnectionStatus = ConnectionStatus::Off;
    else if (currentSessionStatus == SessionStatus::InProgress)
        currentConnectionStatus = ConnectionStatus::Treatment;
    else if (eegHeadset->isConnected())
        currentConnectionStatus = ConnectionStatus::Contact;
    else
        currentConnectionStatus = ConnectionStatus::ContactLost;
}

void NeuresetDevice::calculateBaselineAverages()
{
    qDebug("Baseline averages totally calculated.");
}

void NeuresetDevice::setEEGHeadset(EEGHeadset *eegHeadset)
{
    this->eegHeadset = eegHeadset;
}

void NeuresetDevice::eegHeadsetConnected()
{
    // If in treatment and not paused, resume treatment.
    // TODO - add this.
    updateConnectionStatus();
}

void NeuresetDevice::eegHeadsetDisconnected()
{
    // Check if headset connection lost while in a session
    if (currentScreen == Screen::InSession)
        connectionLossPauseSession();  // also updates connection status within its call
    // Else just update connection status
    else
        updateConnectionStatus();
}

Session* NeuresetDevice::getCurrentSession() { return currentSession; }

int NeuresetDevice::getBatteryLevel() { return batteryLevel; }

NeuresetDevice::ConnectionStatus NeuresetDevice::getCurrentConnectionStatus() { return currentConnectionStatus; }

NeuresetDevice::SessionStatus NeuresetDevice::getCurrentSessionStatus() {return currentSessionStatus; }

NeuresetDevice::Screen NeuresetDevice::getCurrentScreen() { return currentScreen; }

bool NeuresetDevice::isConnected() { return eegHeadset->isConnected(); }

bool NeuresetDevice::isOn() { return deviceOn; }

QDateTime NeuresetDevice::getCurrentDateTime() { return currentDateTime; }

void NeuresetDevice::setCurrentDateTime(QDateTime dt) { currentDateTime = dt; }

void NeuresetDevice::setCurrentScreen(Screen screen) { currentScreen = screen; }
