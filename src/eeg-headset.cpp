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

std::vector<std::vector<float>> EEGHeadset::getSignal(int siteIndex, Band band) {
/**
 * Retrieves a wave signal from a specified EEGHeadset site, formatted as a series of (time, amplitude) points.
 * This function serves as an API endpoint for the model layer, facilitating the visualization of EEG data on the UI.
 *
 * @param siteIndex Index of the EEGHeadset site from which to retrieve the signal.
 * @param band Specifies the frequency band for filtering the wave signal. The Band enum can be one of the following:
 *        - Band::All: Returns the composite wave signal, which is the superposition of all frequency components at the site.
 *        - Other Band values (e.g., Band::Gamma, Band::Beta): Returns the wave signal filtered to include only the frequencies within the specified band.
 *
 * The function outputs the signal as a vector of (time, amplitude) pairs, where each pair represents a point in the waveform. This output is suitable for graphical representation in the UI, showing either the entire spectrum of brainwave activity or focusing on a specific frequency band.
*/
  return electrodes[siteIndex]->collectWaveData(band);
}
