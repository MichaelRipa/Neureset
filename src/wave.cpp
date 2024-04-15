#include "wave.h"
#include <random>

Wave::Wave(float minFreq, float maxFreq, float minAmp, float maxAmp) : minFreq(minFreq), maxFreq(maxFreq), minAmp(minAmp), maxAmp(maxAmp) {}

Wave::~Wave() {}

void Wave::initializeWaveform() {
  frequencies.resize(3); // Ensure there are 3 elements for 3 sine waves
  amplitudes.resize(3);
  for (int i = 0; i < 3; ++i) {
    frequencies[i] = randomFloat(minFreq, maxFreq);
    amplitudes[i] = randomFloat(minAmp, maxAmp);
  }
  
  // After initializing, calculate the dominant frequency
}

void Wave::calculateDominantFrequency() {
  // Returns the dominant frequency w.r.t simplified formula
}

void Wave::applyFrequencyOffset(float offset) {
  // Adds offset to frequency of each component
  for (int i = 0; i < 3; ++i) {
    frequencies[i] += offset;
  }
}

std::vector<float> Wave::getCurrentWaveform(int numPoints) const {
  // Computes a wave to plot with respect to the current frequencies and amplitudes.
}

float Wave::randomFloat(float min, float max) const {
  // Helper function to generate a random float within a specified range
  static std::random_device rd; // Obtain a random number from hardware
  static std::mt19937 eng(rd()); // Seed the generator
  std::uniform_real_distribution<> distr(min, max); // Define the range
  return distr(eng);
}
