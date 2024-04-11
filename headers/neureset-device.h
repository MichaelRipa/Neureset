#pragma once
#include "session.h"
#include "eeg-headset.h"
#include "globals.h"

class NeuresetDevice {
public:
    NeuresetDevice(EEGHeadset* headset);
    ~NeuresetDevice();
    SessionStatus getSessionStatus();
    void startSession();
    void userPauseSession();
    void connectionLossPauseSession();
    void endSession();
    void checkBattery();
    void checkConnection();
    
private:
    Session* session;
    EEGHeadset* headset;
    int batteryLevel;
    bool connected;
    SessionStatus sessionStatus;
    Screen currentScreen;
};
