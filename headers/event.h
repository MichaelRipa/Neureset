#ifndef EVENT_H
#define EVENT_H
#include <variant>
#include <memory>
#include <any>
#include "globals.h"

class Event {
  public:
    Event(EventType type, int time);

    EventType getType();
    int getTime() const;

  private:
    EventType type;
    int time;
};

#endif 
