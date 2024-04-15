#include "electrode.h"

Electrode::Electrode(int numBands) : numBands(numBands) {}

Electrode::~Electrode() {}

void Electrode::initializeElectrode() {
  // Initializes wave with all the band parameters
}

void Electrode::computeBaselineFrequencies() {
  // Computes the baseline frequencies for each wave
}

void Electrode::applyTreatmentToWaves(float offset) {
  // Applies the treatment to the waves
}

std::vector<std::vector<float>> Electrode::collectWaveData(int numPointsPerWave) const {
  // Collects data from all waves for the current time point for plotting or analysis
}
