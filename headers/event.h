#ifndef EVENT_H
#define EVENT_H
#include <variant>
#include <memory>
#include <any>

class Event {
  public:
    Event(int t, int type, std::any source) : time(t), eventType(type), eventSource(source) {}
    int getEventType();
    int getTime() const;
    std::any getEventSource();
  private:
    int eventType;
    int time;
    std::any eventSource; // This will hold a pointer reference to the object to be acted upon when the event takes place.
};

#endif 
