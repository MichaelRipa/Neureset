#pragma once
#include "session.h"
#include "eeg-headset.h"
#include "pc-interface.h"
#include "globals.h"
#include <QDateTime>
#include <QObject>
#include <vector>

class NeuresetDevice: public QObject
{
Q_OBJECT

public:
    // Enums
    enum class SessionStatus { NotStarted, InProgress, UserPausedSession, ConnectionLossPausedSession, UserStoppedSession, Completed };
    enum class ConnectionStatus { Contact, Treatment, ContactLost, Off };
    // enum class Device { On, Off};
    enum class Battery { Dead, Alive, Charging};
    enum Screen {Off, MainMenu, InSession, SessionCompleted, SessionErased, SessionLogs, DateAndTime};

    NeuresetDevice();
    ~NeuresetDevice();

    void startSession();
    void runCurrentSessionStage();  // Runs the current session step (e.g compute post treatment frequencies)
    void userStopSession();
    void userPauseSession();
    void userUnpauseSession();
    void connectionLossPauseSession();

    // General function for ending the session before treatment is complete (due to stop pressed / pause timeout)
    void stopSession();

    void clearAllSessions();
    void uploadAllSessions();

    // In-session treatment related functions
    void calculateBaselineAverages();
    void calculateFrequencyAtCurrentSite();
    void endTreatmentCurrentSite();
    void applyTreatmentToCurrentSite();


    void setEEGHeadset(EEGHeadset* eegHeadset);

    void eegHeadsetConnected();
    void eegHeadsetDisconnected();

    void updateConnectionStatus();

    void setBatteryLevel(int);

    void turnOn();
    void turnOff();

    Session* getCurrentSession();
    std::vector<Session*> getAllSessions();
    PCInterface* getPCInterface();
    int getBatteryLevel();
    ConnectionStatus getCurrentConnectionStatus();
    SessionStatus getCurrentSessionStatus();
    Screen getCurrentScreen();
    bool isConnected();
    bool isOn();
    QDateTime getCurrentDateTime();
    void setCurrentDateTime(QDateTime dt);
    void setCurrentScreen(Screen screen);
    
private:
    EEGHeadset* eegHeadset;
    Session* currentSession = nullptr;
    PCInterface* pcInterface;
    std::vector<Session*> allSessions;

    bool deviceOn;
    QTimer* batteryDrainTimer;
    int batteryLevel;
    //bool connected; <-- For now, connected iff eeg headset connected
    ConnectionStatus currentConnectionStatus;
    SessionStatus currentSessionStatus;
    Screen currentScreen;
    QDateTime currentDateTime;

private slots:
    void decreaseBatteryLevel();
};
