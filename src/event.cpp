#include "event.h"


Event::Event(EventType type, int time)
: type(type), time(time)
{}


Event::EventType Event::getType() {
  return type;
}

int Event::getTime() const {
  return time;
}
