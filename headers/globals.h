#pragma once

extern const int TICKS_PER_SECOND;
enum class SessionStatus { NotStarted, InProgress, Paused, Completed };
enum class Light { Red, Green, Blue, Off };
enum class Device { On, Off};
enum class Battery { Dead, Alive, Charging};
enum class Headset { Connected, Disconnected};
enum class Screen {MainMenu, SessionScreen SessionPaused, SessionStopped, SessionLogs, TimeAndDate, ScreenOff, Admin, PC};
enum class Band { Alpha, Beta, Delta, Theta};
