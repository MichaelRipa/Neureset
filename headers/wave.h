#ifndef WAVE_H
#define WAVE_H

#include "globals.h"
#include <vector>
#include <cmath>

class Wave {
public:
    Wave(float minFreq, float maxFreq, float minAmp, float maxAmp);
    ~Wave();

    // Generates initial random frequencies and amplitudes within specified ranges
    void initializeWaveform();

    // Recalculates the dominant frequency based on current frequencies and amplitudes
    void calculateDominantFrequency();

    // Applies an offset to the frequencies as part of the treatment
    void applyFrequencyOffset(float offset);

    // Returns the current waveform data points for plotting
    std::vector<float> getCurrentWaveform() const;
    // Returns what would be the domain of the waveform (for plotting)
    std::vector<float> getTimeSteps() const;

private:
    float minFreq, maxFreq; // Minimum and maximum frequencies for the band
    float minAmp, maxAmp;   // Minimum and maximum amplitudes for the band
    std::vector<float> frequencies; // Current frequencies of the three sine waves
    std::vector<float> amplitudes;  // Current amplitudes of the three sine waves
    float dominantFrequency;        // Current dominant frequency

    // Helper to generate a random float within a specified range
    float randomFloat(float min, float max) const;
};

#endif // WAVE_H
