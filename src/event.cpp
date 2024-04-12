#include "event.h"


Event::Event(EventType type, int timeOffset)
: type(type), timeOffset(timeOffset)
{}


EventType Event::getType() {
  return type;
}

int Event::getTimeOffset() const {
  return timeOffset;
}
