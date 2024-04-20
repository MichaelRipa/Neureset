#ifndef ELECTRODE_H
#define ELECTRODE_H

#include "globals.h"
#include "wave.h"
#include <vector>
#include <map>
#include <utility>

class Electrode {
public:
  
  Electrode(int numBands);
  ~Electrode();
  
  void initializeElectrode();

  void setConnectionStatus(bool c);

  bool getConnectionStatus();

  // Computes the baseline frequencies for all waves
  void computeBaselineFrequencies();

  // Applies the treatment to the waves based on user input or treatment logic
  void applyTreatmentToWaves(float offset);

  // Collects data from all waves for the current time point for plotting or analysis
  std::vector<std::vector<float>> collectWaveData(Band band) const;

private:
  int numBands;
  bool connectionStatus; // TODO: Enum?
  std::vector<Wave> waves; // Waves corresponding to different frequency bands
};

#endif // ELECTRODE_H
