#include "eeg-headset.h"
#include "neureset-device.h"

EEGHeadset::EEGHeadset(int numSites)
    : numSites(numSites), connected(false) {}

EEGHeadset::~EEGHeadset() {}

void EEGHeadset::setNeuresetDevice(NeuresetDevice *neuresetDevice)
{
    this->neuresetDevice = neuresetDevice;
}

void EEGHeadset::connect()
{
    if (connected)
        return;
    connected = true;
    neuresetDevice->eegHeadsetConnected();

}

void EEGHeadset::disconnect()
{
    if (!connected)
        return;
    connected = false;
    neuresetDevice->eegHeadsetDisconnected();

}

int EEGHeadset::getNumSites() { return numSites; }

bool EEGHeadset::isConnected() const {
    return connected;
}

std::vector<double> EEGHeadset::getSignal(int siteIndex) {
    // Placeholder implementation
    return std::vector<double>();
}
