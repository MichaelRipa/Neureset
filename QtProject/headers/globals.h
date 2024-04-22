#pragma once

#include <map>
#include <string>
#include <utility>
#include <QString>

extern const int TICKS_PER_SECOND;
extern const int NUM_SITES;
extern const int TIME_TO_COMPUTE_FREQUENCY;
extern const int SESSION_PAUSED_TIMEOUT;
extern const int MESH_PRECISION;
extern const float OFFSET_FREQUENCY;
extern const QString PC_FILENAME;

// Session treament related time values (in ms)
extern const int SITE_TREATMENT_DURATION;
extern const int SITE_TREATMENT_AMOUNT;  // If duration is 1 second and treatment amount is 16, offset applied every 1/16 second

extern const int BATTERY_DRAIN_FREQUENCY;

//enum class SessionStatus { NotStarted, InProgress, Paused, Completed };
//enum class Light { Red, Green, Blue, Off };
//enum class Device { On, Off};
//enum class Battery { Dead, Alive, Charging};
//enum class ConnectionStatus { Connected, Disconnected};
//enum class Screen {MainMenu, InSession, SessionErased, SessionCompleted, SessionLogs, DateAndTime, Off};
enum class Band { 
  Gamma = 0, 
  Beta, 
  Alpha, 
  Theta, 
  All, 
  NUM_BANDS
}; 

const std::map<Band, std::pair<float, float>> frequencyRanges = {
    {Band::Gamma, {30.0, 100.0}},
    {Band::Beta, {12.0, 30.0}},
    {Band::Alpha, {8.0, 12.0}},
    {Band::Theta, {4.0, 8.0}}
};


std::string bandMap(Band band);

Band stringToBand(QString bandStr);
