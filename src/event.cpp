#include "event.h"


Event::Event(EventType type, int time)
: type(type), time(time)
{}


EventType Event::getType() {
  return type;
}

int Event::getTime() const {
  return time;
}
