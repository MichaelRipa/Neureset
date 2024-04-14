#ifndef EVENT_H
#define EVENT_H
#include <variant>
#include <memory>
#include <any>


class Event {
  public:
    enum class EventType { CalculateBaselineAverages };

    Event(EventType type, int time);

    EventType getType();
    int getTime() const;

  private:
    EventType type;
    int time;
};

#endif 
