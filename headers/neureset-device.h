#pragma once
#include "session.h"

class NeuresetDevice {
public:
    NeuresetDevice(Headset* headset);
    ~NeuresetDevice();
    bool getSessionStatus();
    void startSession();
    void pauseSession();
    void endSession();
    void checkBattery();
    void checkConnection();
    
private:
    Session* session;
    Headset* headset;
    int batteryLevel;
    bool connectionStatus;
};
