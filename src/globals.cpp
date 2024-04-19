#include "globals.h"

const int TICKS_PER_SECOND = 10000;
const int NUM_SITES = 7;
const int TIME_TO_COMPUTE_FREQUENCY = 5000;
const int SESSION_PAUSED_TIMEOUT = 5000;
const int MESH_PRECISION = 1000;

std::string bandMap(Band band) {
  switch (band) {
  case Band::Gamma: return "Gamma";
  case Band::Beta: return "Beta";
  case Band::Alpha: return "Alpha";
  case Band::Theta: return "Theta";
  case Band::All: return "All";
  default: return "Unknown Band";
  } 
}
