#pragma once
#include "session.h"
#include "eeg-headset.h"
#include "globals.h"

class Model; // Forward reference

class NeuresetDevice {
public:
    NeuresetDevice(Model* model, EEGHeadset* headset);
    ~NeuresetDevice();
    SessionStatus getSessionStatus();
    void startSession();
    void userPauseSession();
    void connectionLossPauseSession();
    void endSession();
    void checkBattery();
    void checkConnection();
    
private:
    Model* model;
    Session* session;
    EEGHeadset* headset;
    int batteryLevel;
    bool connected;
    SessionStatus sessionStatus;
    Screen currentScreen;
};
