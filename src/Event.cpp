#include "Event.h"


int Event::getEventType() {
  return eventType;
}

int Event::getTime() const {
  return time;      
}

std::any Event::getEventSource(){
  return eventSource;
}
