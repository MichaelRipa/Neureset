#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#include <vector>
#include "electrode.h"

class NeuresetDevice; // Forward reference

class EEGHeadset {

public:
    EEGHeadset(int numSites);
    ~EEGHeadset();

    void setNeuresetDevice(NeuresetDevice* neuresetDevice);
    void connect();
    void disconnect();

    int getNumSites();
    bool isConnected() const;
    int getBandRangeAtSite(int siteIndex);
    std::vector<double> getSignal(int siteIndex);
private:
    NeuresetDevice* neuresetDevice;
    std::vector<Electrode*> electrodes;
    int numSites;
    bool connected;
    std::vector<int> siteBandRanges;
    std::vector<double> generateWave(int siteIndex, float startTime, float endTime);
};
#endif
