#include "neureset-device.h"
#include <vector>
#include <QDebug>
#include <model.h>
#include "event.h"


NeuresetDevice::NeuresetDevice()
    : deviceOn(true), batteryDrainTimer(new QTimer(this)), batteryLevel(100),
      currentScreen(Screen::MainMenu), currentConnectionStatus(ConnectionStatus::ContactLost),
      currentDateTime(QDate(1970, 1, 1), QTime(0,0,0)), currentSessionStatus(SessionStatus::NotStarted), pcInterface(new PCInterface)
{
    batteryDrainTimer->start(BATTERY_DRAIN_FREQUENCY);

    // --- Callback connections ---
    connect(batteryDrainTimer, SIGNAL(timeout()), this, SLOT(decreaseBatteryLevel()));
}

NeuresetDevice::~NeuresetDevice() {
  delete pcInterface;
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
        updateConnectionStatus();

        currentSession = new Session(eegHeadset->getNumSites(), currentDateTime);
        eegHeadset->reinitializeElectrodes(); // Ensures frequencies are refreshed between sessions
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
        qDebug("Computing pre-treatment frequencies..");
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, TIME_TO_COMPUTE_FREQUENCY);
    }
    // If at this stage, treatment is applied to the next site
    else if (currentSession->getStage() == Session::Stage::ApplyTreatmentToSites) {
        // Compute dominant frequencies event. Once done, it will create further events for adding treatment (and eventually ending).
        qDebug("Site %d: Calculating baseline frequency.", currentSession->getTreatmentCurrentSite());
        Model::Instance()->addToEventQueue(Event::EventType::CalculateFrequencyAtCurrentSite, TIME_TO_COMPUTE_FREQUENCY);
    }
    else if (currentSession->getStage() == Session::Stage::computePostTreatmentBaselines) {
                qDebug("Computing post-treatment frequencies..");
        Model::Instance()->addToEventQueue(Event::EventType::CalculateBaselineAverages, TIME_TO_COMPUTE_FREQUENCY);
        Model::Instance()->stateChanged();
    }
}

// Pauses a session when user specifies
void NeuresetDevice::userPauseSession() {
    currentSessionStatus = SessionStatus::UserPausedSession;
    updateConnectionStatus();
    Model::Instance()->clearTreatmentEvents();
    Model::Instance()->addToEventQueue(Event::EventType::UserPausedSession, SESSION_PAUSED_TIMEOUT);
}

void NeuresetDevice::userUnpauseSession()
{
    // Remove the pending pause timeout
    Model::Instance()->clearEventType(Event::EventType::UserPausedSession);

    if (eegHeadset->isConnected()) {
        currentSessionStatus = SessionStatus::InProgress;
    }
    // Case where session unpaused but connection lost
    else {
        currentSessionStatus = SessionStatus::ConnectionLossPausedSession;
    }
    updateConnectionStatus();
}


void NeuresetDevice::connectionLossPauseSession() {
    if (currentSessionStatus != SessionStatus::UserPausedSession)
        currentSessionStatus = SessionStatus::ConnectionLossPausedSession;
    updateConnectionStatus();
    Model::Instance()->clearTreatmentEvents();
    Model::Instance()->addToEventQueue(Event::EventType::ConnectionLossPausedSession, SESSION_PAUSED_TIMEOUT);
    Model::Instance()->stateChanged();

}


void NeuresetDevice::stopSession() {
    //currentSession->pauseTimer();
    delete currentSession;
    currentSession = nullptr;
    currentScreen = Screen::SessionErased;
    updateConnectionStatus();
    Model::Instance()->clearAllEvents();
    Model::Instance()->stateChanged();
}


// Called when the user clicks the stop session buttton
void NeuresetDevice::userStopSession() {
    currentSessionStatus = SessionStatus::UserStoppedSession;
    stopSession();
}


void NeuresetDevice::clearAllSessions() {
  for (Session* session : allSessions) {
    delete session;
  }
  allSessions.clear();
}

void NeuresetDevice::uploadAllSessions() {
  if (allSessions.size() != 0) {
    pcInterface->uploadData(allSessions);
    // Once data is uploaded, can clear list to avoid duplicate uploads
    clearAllSessions();
  }
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

void NeuresetDevice::setBatteryLevel(int batteryLevel)
{
    this->batteryLevel = batteryLevel;
}

void NeuresetDevice::turnOn()
{
    if (batteryLevel > 0) {
        deviceOn = true;
        currentScreen = Screen::MainMenu;
        currentSessionStatus = SessionStatus::NotStarted;
        updateConnectionStatus();
    }
    Model::Instance()->stateChanged();
}

void NeuresetDevice::turnOff() {
    deviceOn = false;
    currentScreen = Screen::Off;
    currentSessionStatus = SessionStatus::NotStarted;
    updateConnectionStatus();

    // Case user was in the middle of a session
    if (currentSession) {
        delete currentSession;
        currentSession = nullptr;
    }
    Model::Instance()->clearAllEvents(); // If in middle of session, any running/pending work is discarded
    Model::Instance()->stateChanged();

}

void NeuresetDevice::calculateBaselineAverages()
{
    eegHeadset->computeBaselineFrequencies();

    qDebug("Baseline averages calculated.");

    // If computed pre-treatment baseline frequencies, start offset frequency treatment processs
    if (currentSession->getStage() == Session::Stage::computePreTreatmentBaselines) {
        currentSession->setBaselineFrequenciesBefore(eegHeadset->getBaselineFrequencies());
        currentSession->setStage(Session::Stage::ApplyTreatmentToSites);
    }
    // If computed post-treatment baseline frequencies, done treatment
    else if (currentSession->getStage() == Session::Stage::computePostTreatmentBaselines) {
        currentSession->setBaselineFrequenciesAfter(eegHeadset->getBaselineFrequencies());
        qDebug("Done treatment!");
        allSessions.push_back(currentSession);
        currentScreen = Screen::SessionCompleted;
        Model::Instance()->stateChanged();
    }
}

void NeuresetDevice::calculateFrequencyAtCurrentSite()
{
    int currentSite = currentSession->getTreatmentCurrentSite();
    int timePerSubTreatment = SITE_TREATMENT_DURATION / SITE_TREATMENT_AMOUNT;

    qDebug("Site %d pre-treatment frequency: %f", currentSite, 3.0);
    // qDebug("Time per sub-treatment: %d", timePerSubTreatment);

    // Add treatment events (which compute the freq and apply offset, and timed so this processs is every 1/16th of a sceond)
    for (int i = 1; i <= SITE_TREATMENT_AMOUNT; i++) {
        Model::Instance()->addToEventQueue(Event::EventType::ApplyTreatmentToCurrentSite, timePerSubTreatment * i);
    }
    Model::Instance()->addToEventQueue(Event::EventType::EndTreatmentCurrentSite, timePerSubTreatment * (SITE_TREATMENT_AMOUNT+1));
}

void NeuresetDevice::endTreatmentCurrentSite() {
    int currentSite = currentSession->getTreatmentCurrentSite();
    qDebug("Site %d: Treatment complete.", currentSite);
    // Go to next site or end site treatment if at last site
    if (currentSite < eegHeadset->getNumSites())
        currentSession->setTreatmentCurrentSite(currentSite + 1);
    else
        currentSession->setStage(Session::Stage::computePostTreatmentBaselines);

}

void NeuresetDevice::applyTreatmentToCurrentSite()
{
    int currentSite = currentSession->getTreatmentCurrentSite();

    qDebug("Site %d: Current frequency is %f", currentSite, 3.2);
    qDebug("Site %d: Adding +%f offset", currentSite, 5.0);
    eegHeadset->applyTreatmentToSite(currentSite - 1, OFFSET_FREQUENCY);
}

void NeuresetDevice::setEEGHeadset(EEGHeadset *eegHeadset)
{
    this->eegHeadset = eegHeadset;
}

void NeuresetDevice::eegHeadsetConnected()
{
    Model::Instance()->clearEventType(Event::EventType::ConnectionLossPausedSession);
    // can resume session treatment if in session unless paused by user explicitely
    if (currentScreen == Screen::InSession && currentSessionStatus == SessionStatus::ConnectionLossPausedSession) {
        currentSessionStatus = SessionStatus::InProgress;
    }
    // If in treatment and not paused, resume treatment.
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

std::vector<Session*> NeuresetDevice::getAllSessions() { return allSessions;
}

PCInterface* NeuresetDevice::getPCInterface() { return pcInterface; }

int NeuresetDevice::getBatteryLevel() { return batteryLevel; }

NeuresetDevice::ConnectionStatus NeuresetDevice::getCurrentConnectionStatus() { return currentConnectionStatus; }

NeuresetDevice::SessionStatus NeuresetDevice::getCurrentSessionStatus() {return currentSessionStatus; }

NeuresetDevice::Screen NeuresetDevice::getCurrentScreen() { return currentScreen; }

bool NeuresetDevice::isConnected() { return eegHeadset->isConnected(); }

bool NeuresetDevice::isOn() { return deviceOn; }

QDateTime NeuresetDevice::getCurrentDateTime() { return currentDateTime; }

void NeuresetDevice::setCurrentDateTime(QDateTime dt) { currentDateTime = dt; }

void NeuresetDevice::setCurrentScreen(Screen screen) { currentScreen = screen; }

void NeuresetDevice::decreaseBatteryLevel()
{
    if (!deviceOn)
        return;
    if (batteryLevel > 0) {
        batteryLevel--;
        Model::Instance()->stateChanged();
    }
    if (batteryLevel == 0) {
        turnOff();
    }
}
