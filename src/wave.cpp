#include "wave.h"
#include <random>
#include <cmath>
#include <stdexcept>

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
  if (frequencies.size() != amplitudes.size()) {
    throw std::runtime_error("Frequencies and amplitudes vectors must be of the same size.");
  }

  float numerator = 0.0;
  float denominator = 0.0;

  for (size_t i = 0; i < frequencies.size(); ++i) {
    numerator += frequencies[i] * std::pow(amplitudes[i], 2);
    denominator += std::pow(amplitudes[i], 2);
  }

  if (denominator == 0) {
    std::runtime_error("Sum of the squares of amplitudes is zero, cannot divide by zero.");
  } 
  dominantFrequency = numerator / denominator; 
}

void Wave::applyFrequencyOffset(float offset) {
  // Adds offset to frequency of each component
  for (int i = 0; i < 3; ++i) {
    frequencies[i] += offset;
  }
}

std::vector<float> Wave::getCurrentWaveform(int numPoints) const {
  // Computes a wave to plot with respect to the current frequencies and amplitudes.
  std::vector<float> waveform(numPoints);

  // TODO: In future implementations, the timeStep should also be based on a timeStart and timeEnd
  // I.e. supporting returning data for a simulated real-time signal
  float timeStep = 1.0 / numPoints;  // Adjust timeStep based on the actual time span you wish to cover

  for (int i = 0; i < numPoints; ++i) {
    float t = i * timeStep;  // Current time point
    float wavePoint = 0.0;

  // Sum the contributions of each sinusoidal component
  for (size_t j = 0; j < frequencies.size(); ++j) {
    wavePoint += amplitudes[j] * std::sin(2 * M_PI * frequencies[j] * t);
  }

  waveform[i] = wavePoint;
  }

  return waveform;
}

float Wave::randomFloat(float min, float max) const {
  // Helper function to generate a random float within a specified range
  static std::random_device rd; // Obtain a random number from hardware
  static std::mt19937 eng(rd()); // Seed the generator
  std::uniform_real_distribution<> distr(min, max); // Define the range
  return distr(eng);
}
