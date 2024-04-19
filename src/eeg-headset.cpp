#include "eeg-headset.h"
#include "neureset-device.h"

EEGHeadset::EEGHeadset(int numSites)
    : numSites(numSites), connected(false) {
  for (int i = 0; i < numSites; ++i) {
    electrodes.push_back(new Electrode(4));
  }
}

EEGHeadset::~EEGHeadset() {
  for (int i = 0; i < numSites; ++i) {
    delete electrodes[i];
  }
}

void EEGHeadset::setNeuresetDevice(NeuresetDevice *neuresetDevice)
{
    this->neuresetDevice = neuresetDevice;
}

void EEGHeadset::connect()
{
    if (connected)
        return;
    // This is just a trivial implementation where either all sites are connected or disconnected
    for (int i = 0; i < numSites; ++i) {
      electrodes[i]->setConnectionStatus(true);
     }
    connected = true;
    neuresetDevice->eegHeadsetConnected();

}

void EEGHeadset::disconnect()
{
    if (!connected)
        return;
    // This is just a trivial implementation where either all sites are connected or disconnected
    for (int i = 0; i < numSites; ++i) {
      electrodes[i]->setConnectionStatus(false);
     }
    connected = false;
    neuresetDevice->eegHeadsetDisconnected();
}

int EEGHeadset::getNumSites() { return numSites; }

bool EEGHeadset::isConnected() const {
    for (int i = 0; i < numSites; ++i) {
      if (!electrodes[i]->getConnectionStatus()){
        return false;
      }
    } 
  return true;
}

std::vector<double> EEGHeadset::getSignal(int siteIndex) {
    // Placeholder implementation
    return std::vector<double>();
}
