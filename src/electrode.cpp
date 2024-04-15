#include "electrode.h"

Electrode::Electrode(int numBands) : numBands(numBands) {}

Electrode::~Electrode() {}

void Electrode::initializeElectrode() {
  // Initializes wave with all the band parameters
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
