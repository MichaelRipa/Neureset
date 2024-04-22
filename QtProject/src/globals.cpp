#include "globals.h"

const int TICKS_PER_SECOND = 10000;
const int NUM_SITES = 7;
const int TIME_TO_COMPUTE_FREQUENCY = 5000;
const int SESSION_PAUSED_TIMEOUT = 5000;
const int MESH_PRECISION = 1000;
const float OFFSET_FREQUENCY = 0.078125;
const QString PC_FILENAME = "pc-session-logs.csv";

const int SITE_TREATMENT_DURATION = 1000;
const int SITE_TREATMENT_AMOUNT = 16;

const int BATTERY_DRAIN_FREQUENCY = 2000;  // How long until battery drains 1 percent

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

// Helper function to convert QString to Band enum
Band stringToBand(QString bandStr) {
    if (bandStr == "Gamma") return Band::Gamma;
    if (bandStr == "Beta")  return Band::Beta;
    if (bandStr == "Alpha") return Band::Alpha;
    if (bandStr == "Theta") return Band::Theta;
    if (bandStr == "All") return Band::All;
}
