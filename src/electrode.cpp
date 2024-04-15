#include "electrode.h"

Electrode::Electrode(int numBands) : numBands(numBands) {}

Electrode::~Electrode() {}

// Initialization of the static map
const std::map<Electrode::Band, std::pair<float, float>> Electrode::frequencyRanges = {
    {Band::Gamma, {30.0, 100.0}},
    {Band::Beta, {12.0, 30.0}},
    {Band::Alpha, {8.0, 12.0}},
    {Band::Theta, {4.0, 8.0}}
};

void Electrode::initializeElectrode() {
    int index = 0;
    for (auto& band : frequencyRanges) {
        // Initialize each wave with the frequency and amplitude range
        waves[index++] = Wave(band.second.first, band.second.second, 0.5, 3.0);
    }
}

void Electrode::computeBaselineFrequencies() {
  // Computes the baseline frequencies for each wave
  for (size_t i = 0; i < waves.size(); ++i) {
    waves[i].calculateDominantFrequency();
  }
}

void Electrode::applyTreatmentToWaves(float offset) {
  // Applies the treatment to the waves
  for (size_t i = 0; i < waves.size(); ++i) {
    waves[i].applyFrequencyOffset(offset);
  }
}

std::vector<std::vector<float>> Electrode::collectWaveData(int numPointsPerWave) const {
  // Collects data from all waves for the current time point for plotting or analysis
  std::vector<std::vector<float>> waveData(waves.size());
  for (size_t i = 0; i < waves.size(); ++i) {
    waveData[i] = waves[i].getCurrentWaveform(numPointsPerWave);
  }
  return waveData;
}
