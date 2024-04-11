#pragma once
#include "session.h"
#include "eeg-headset.h"

class NeuresetDevice {
public:
    NeuresetDevice(EEGHeadset* headset);
    ~NeuresetDevice();
    bool getSessionStatus();
    void startSession();
    void pauseSession();
    void endSession();
    void checkBattery();
    void checkConnection();
    
private:
    Session* session;
    EEGHeadset* headset;
    int batteryLevel;
    bool connectionStatus;
};
