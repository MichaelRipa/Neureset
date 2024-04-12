#ifndef EVENT_H
#define EVENT_H
#include <variant>
#include <memory>
#include <any>
#include "globals.h"

class Event {
  public:
    Event(EventType type, int timeOffset);

    EventType getType();
    int getTimeOffset() const;

  private:
    EventType type;
    int timeOffset;
};

#endif 
