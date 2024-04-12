#pragma once

extern const int TICKS_PER_SECOND;
extern const int NUM_SITES;
enum class SessionStatus { NotStarted, InProgress, Paused, Completed };
enum class Light { Red, Green, Blue, Off };
enum class Device { On, Off};
enum class Battery { Dead, Alive, Charging};
enum class ConnectionStatus { Connected, Disconnected};
enum class Screen {MainMenu, InSession, SessionErased, SessionCompleted, SessionLogs, DateAndTime, Off};
enum class Band { Alpha, Beta, Delta, Theta};
enum class EventType { CalculateBaselineAverages };
