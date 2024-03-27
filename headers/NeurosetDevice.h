#pragma once
#include "Session.h"

class NeurosetDevice {
public:
    NeurosetDevice();
    ~NeurosetDevice();
    void startSession();
    void pauseSession();
    void endSession();
    void checkBattery();
    void checkConnection();
private:
    Session currentSession;
    int batteryLevel;
    bool connectionStatus;
};
