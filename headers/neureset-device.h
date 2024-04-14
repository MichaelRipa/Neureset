#pragma once
#include "session.h"
#include "eeg-headset.h"
#include "globals.h"

class NeuresetDevice {
public:
    // Enums
    enum class SessionStatus { NotStarted, InProgress, Paused, Completed };
    enum class Light { Red, Green, Blue, Off };
    // enum class Device { On, Off};
    enum class Battery { Dead, Alive, Charging};
    enum Screen {Off, MainMenu, InSession, SessionErased, SessionCompleted, SessionLogs, DateAndTime};

    NeuresetDevice();
    ~NeuresetDevice();

    void startSession();
    void pauseSession();
    void userPauseSession();
    void connectionLossPauseSession();
    void stopSession();

    void calculateBaselineAverages();

    void setEEGHeadset(EEGHeadset* eegHeadset);

    void connectionStatusChanged();

    Session* getCurrentSession();
    int getBatteryLevel();
    Light getCurrentLight();
    SessionStatus getCurrentSessionStatus();
    Screen getCurrentScreen();
    bool isConnected();
    bool isOn();



    
private:
    EEGHeadset* eegHeadset;
    Session* currentSession;

    bool deviceOn;
    int batteryLevel;
    //bool connected; <-- For now, connected iff eeg headset connected
    Light currentLight;
    SessionStatus currentSessionStatus;
    Screen currentScreen;


};
