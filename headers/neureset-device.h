#pragma once
#include "session.h"
#include "eeg-headset.h"
#include "globals.h"
#include <QDateTime>

class NeuresetDevice {
public:
    // Enums
    enum class SessionStatus { NotStarted, InProgress, UserPausedSession, ConnectionLossPausedSession, UserStoppedSession, Completed };
    enum class ConnectionStatus { Contact, Treatment, ContactLost, Off };
    // enum class Device { On, Off};
    enum class Battery { Dead, Alive, Charging};
    enum Screen {Off, MainMenu, InSession, SessionErased, SessionCompleted, SessionLogs, DateAndTime};

    NeuresetDevice();
    ~NeuresetDevice();

    void startSession();
    void runCurrentSessionStage();  // Runs the current session step (e.g compute post treatment frequencies)
    void userPauseSession();
    void userUnpauseSession();
    void connectionLossPauseSession();

    void stopSession();

    void calculateBaselineAverages();

    void setEEGHeadset(EEGHeadset* eegHeadset);

    void eegHeadsetConnected();
    void eegHeadsetDisconnected();

    void updateConnectionStatus();

    Session* getCurrentSession();
    int getBatteryLevel();
    ConnectionStatus getCurrentConnectionStatus();
    SessionStatus getCurrentSessionStatus();
    Screen getCurrentScreen();
    bool isConnected();
    bool isOn();
    QDateTime getCurrentDateTime();
    void setCurrentDateTime(QDateTime dt);
    
private:
    EEGHeadset* eegHeadset;
    Session* currentSession;

    bool deviceOn;
    int batteryLevel;
    //bool connected; <-- For now, connected iff eeg headset connected
    ConnectionStatus currentConnectionStatus;
    SessionStatus currentSessionStatus;
    Screen currentScreen;
    QDateTime currentDateTime;
};
