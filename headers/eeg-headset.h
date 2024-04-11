#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#include <vector>

class Model; // Forward reference

class EEGHeadset {

public:
    EEGHeadset(Model* model, int numSites);
    ~EEGHeadset();
    bool isConnected() const;
    int getBandRangeAtSite(int siteIndex);
    std::vector<double> getSignal(int siteIndex);
private:
    Model* model;
    bool contactStatus;
    std::vector<int> siteBandRanges;
    std::vector<double> generateWave(int siteIndex, float startTime, float endTime);
};
#endif
