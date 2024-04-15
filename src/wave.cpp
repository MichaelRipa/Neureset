#include "wave.h"

Wave::Wave(float minFreq, float maxFreq, float minAmp, float maxAmp) : minFreq(minFreq), maxFreq(maxFreq), minAmp(minAmp), maxAmp(maxAmp) {}

Wave::~Wave() {}

void Wave::initializeWaveform() {
  // Sets the frequencies and amplitudes
}

void Wave::calculateDominantFrequency() {
 // Returns the dominant frequency w.r.t simplified formula

}

void applyFrequencyOffset(float offset) {
 // Adds offset to frequency of each component
}

std::vector<float> getCurrentWavefrom(int numPoints) {
  // Computes a wave to plot with respect to the current frequencies and amplitudes.
}
