#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#include <vector>
#include "globals.h"
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
    std::vector<std::vector<float>> getSignal(int siteIndex, Band band);
    void computeBaselineFrequencies();
    float getBaselineFrequencyForSite(int siteIndex);
    std::vector<float> getBaselineFrequencies();
    void applyTreatmentToSite(int siteIndex, float offset);
private:
    NeuresetDevice* neuresetDevice;
    std::vector<Electrode*> electrodes;
    int numSites;
    bool connected;
};
#endif
