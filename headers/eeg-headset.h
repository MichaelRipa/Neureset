#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#import <vector>

class EEGHeadset {
public:
    EEGHeadset(int numSites);
    ~EEGHeadset();
    bool isConnected() const;
    int getBandRangeAtSite(int siteIndex);
    std::vector<double> getSignal(int siteIndex);
private:
    bool contactStatus;
    std::vector<int> siteBandRanges;
    std::vector<double> generateWave(int siteIndex, float startTime, float endTime);
};
#endif
