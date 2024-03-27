#pragma once
class EEGHeadset {
public:
    EEGHeadset();
    ~EEGHeadset();
    bool checkContact() const;
    double getSignal();
private:
    bool contactStatus;
};
