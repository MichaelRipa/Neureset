#ifndef ELECTRODE_H
#define ELECTRODE_H

#include "wave.h"
#include <vector>

class Electrode {
public:
    Electrode(int numBands);
    ~Electrode();

    // Initializes all waves with the appropriate band parameters
    void initializeElectrode();

    // Computes the baseline frequencies for all waves
    void computeBaselineFrequencies();

    // Applies the treatment to the waves based on user input or treatment logic
    void applyTreatmentToWaves(float offset);

    // Collects data from all waves for the current time point for plotting or analysis
    std::vector<std::vector<float>> collectWaveData(int numPointsPerWave) const;

private:
    int numBands;
    std::vector<Wave> waves; // Waves corresponding to different frequency bands
};

#endif // ELECTRODE_H
