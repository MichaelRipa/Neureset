#include "eeg-headset.h"
#include "neureset-device.h"

EEGHeadset::EEGHeadset(int numSites)
    : numSites(numSites), connected(false) {}

EEGHeadset::~EEGHeadset() {}

void EEGHeadset::setNeuresetDevice(NeuresetDevice *neuresetDevice)
{
    this->neuresetDevice = neuresetDevice;
}

void EEGHeadset::setConnected(bool connected)
{
    this->connected = connected;
    neuresetDevice->connectionStatusChanged();
}

int EEGHeadset::getNumSites() { return numSites; }

bool EEGHeadset::isConnected() const {
    return connected;
}

std::vector<double> EEGHeadset::getSignal(int siteIndex) {
    // Placeholder implementation
    return std::vector<double>();
}
