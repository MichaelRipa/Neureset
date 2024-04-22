#include "electrode.h"
#include <QDebug>

Electrode::Electrode(int numBands) : numBands(numBands) {
  int index = 0;
  waves.resize(numBands, nullptr);
  for (auto& band : frequencyRanges) {
    waves[index] = new Wave(band.second.first, band.second.second, 0.1, 1.0);
    index += 1;
  }
    // Initialize each wave with the frequency and amplitude range
  initializeElectrode();
}

Electrode::~Electrode() {
  for (size_t i = 0; i < waves.size(); ++i) {
    delete waves[i];
  }
}

void Electrode::initializeElectrode() {
  for (size_t i = 0; i < waves.size(); ++i) {
    // Sets wave with randomly chosen frequencies and amplitudes (with respect to pre-determined frequency band)
    waves[i]->initializeWaveform();
  }
}

void Electrode::computeBaselineFrequencies() {
  // Computes the baseline frequencies for each wave
  for (size_t i = 0; i < waves.size(); ++i) {
    waves[i]->calculateDominantFrequency();
  }
}

std::vector<float> Electrode::getBaselineFrequencies() {
  std::vector<float> baselineFreqs(waves.size());
  for (size_t i = 0; i < waves.size(); ++i) {
    baselineFreqs[i] = waves[i]->getDominantFrequency();
  }
  return baselineFreqs;
}

void Electrode::applyTreatmentToWaves(float offset) {
  // Applies the treatment to the waves
  for (size_t i = 0; i < waves.size(); ++i) {
    waves[i]->applyFrequencyOffset(offset);
  }
}

std::vector<std::vector<float>> Electrode::collectWaveData(Band band) const {
  // Collects data from all waves for the current time point for plotting or analysis
  std::vector<float> waveDomain = waves[0]->getTimeSteps();
  std::vector<float> waveRange(waveDomain.size());
  int b = static_cast<int>(band);

  if (band == Band::All) {
    // Combines all the bands together into one waveform
    for (size_t i = 0; i < waves.size(); ++i) {
      std::vector<float> currWave = waves[i]->getCurrentWaveform();
      for (size_t j = 0; j < currWave.size(); ++j) {
        waveRange[j] += currWave[j];
      }
    }
  } else {
    // Returns a wave corresponding to a particular band range
    waveRange = waves[b]->getCurrentWaveform();
  }

  // Transforms the data into (t,y) coordinates for plotting
  std::vector<std::vector<float>> waveData;  // Removed the initialization with size
  // Prepare the data for plotting
  for (size_t i = 0; i < waveDomain.size(); ++i) {
    waveData.push_back({waveDomain[i], waveRange[i]}); // Now correctly adding new entries
  }
  return waveData;
}


bool Electrode::getConnectionStatus() {return connectionStatus;}

void Electrode::setConnectionStatus(bool c) {connectionStatus = c;}
