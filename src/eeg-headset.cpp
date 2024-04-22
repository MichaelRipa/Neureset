#include "eeg-headset.h"
#include "neureset-device.h"
#include <QDebug>

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
    qDebug("Connecting.");
    if (connected)
        return;
    qDebug("A");
    // This is just a trivial implementation where either all sites are connected or disconnected
    for (int i = 0; i < numSites; ++i) {
      electrodes[i]->setConnectionStatus(true);
     }
    qDebug("B");
    connected = true;
    neuresetDevice->eegHeadsetConnected();
    qDebug("C");

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

std::vector<float>  EEGHeadset::getBaselineFrequencies() { 
  std::vector<float> freqs(electrodes.size());
  for (size_t i = 0; i < electrodes.size(); ++i) {
    float f = getBaselineFrequencyForSite(i);
    qDebug() << "Frequency at site " << i << " " << f;
    freqs[i] = f;
  }
  return freqs;
}

void EEGHeadset::computeBaselineFrequencies() {
  for (size_t i = 0; i < electrodes.size(); ++i) {
    electrodes[i]->computeBaselineFrequencies();
  }
}

float EEGHeadset::getBaselineFrequencyForSite(int siteIndex) { 
  float frequency = 0;
  std::vector<float> allFreqs = electrodes[siteIndex]->getBaselineFrequencies();
  // We assume that the frequency of the waves added together is the sum of the frequencies of the waves it is made up of.
  for (size_t i = 0; i < allFreqs.size(); ++i) {
    frequency += allFreqs[i];
  }
  return frequency;
}

bool EEGHeadset::isConnected() const {
    for (int i = 0; i < numSites; ++i) {
      if (!electrodes[i]->getConnectionStatus()){
        return false;
      }
    } 
  return true;
}

void EEGHeadset::applyTreatmentToSite(int siteIndex, float offset) {
  electrodes[siteIndex]->applyTreatmentToWaves(offset);
}

void EEGHeadset::reinitializeElectrodes() {
  for (int i = 0; i < numSites; ++i) {
    electrodes[i]->initializeElectrode();
  }
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
