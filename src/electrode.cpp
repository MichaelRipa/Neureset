#include "electrode.h"

Electrode::Electrode(int numBands) : numBands(numBands) {}

Electrode::~Electrode() {}

// Initialization of the static map
const std::map<Band, std::pair<float, float>> Electrode::frequencyRanges = {
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
        waves[index].initializeWaveform();
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

std::vector<std::vector<float>> Electrode::collectWaveData(Band band) const {
  // Collects data from all waves for the current time point for plotting or analysis
  std::vector<float> waveDomain = waves[0].getTimeSteps();
  std::vector<float> waveRange(waveDomain.size());
  int b = static_cast<int>(band);

  if (band == Band::All) {
    // Combines all the bands together into one waveform
    for (size_t i = 0; i < waves.size(); ++i) {
      std::vector<float> currWave = waves[i].getCurrentWaveform();
      for (size_t j = 0; j < currWave.size(); ++j) {
        waveRange[j] += currWave[j];
      }
    }
  }

  else {
    // Returns a wave cooresponding to a particular band range
    waveRange = waves[b].getCurrentWaveform();
  }

  // Transforms the data into (t,y) coordinates for plotting
  std::vector<std::vector<float>> waveData(waveDomain.size());
  for (size_t i = 0; i < waveDomain.size(); ++i) {
    std::vector<float> currCoordinate(2);
    currCoordinate[0] = waveDomain[i];
    currCoordinate[1] = waveRange[i];
  }
  return waveData;
}

bool Electrode::getConnectionStatus() {return connectionStatus;}

void Electrode::setConnectionStatus(bool c) {connectionStatus = c;}
