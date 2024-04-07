#pragma once

class Session {
public:
    Session();
    ~Session();
    void calculateBaseline();
    void applyTreatment();
    void saveSessionData();
private:
    int sessionId;
    double startTime;
    double endTime;
    double progress;
    double baselineData;
    double treatmentData;
};
