#pragma once

extern const int TICKS_PER_SECOND;
extern const int NUM_SITES;
extern const int TIME_TO_COMPUTE_FREQUENCY;
extern const int SESSION_PAUSED_TIMEOUT;
extern const int MESH_PRECISION;

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
  All 
}; 
