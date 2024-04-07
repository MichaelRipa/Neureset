#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "event.h"
#include <vector>
using namespace std;

class EventQueue {
  public:
    static EventQueue& getInstance() {
      static EventQueue instance;
      return instance;
    }
    EventQueue(EventQueue const&) = delete;
    void operator=(EventQueue const&) = delete;
    void addEvent(const Event& event);
    vector<Event> getEventsForTime(int time);
  private:
    EventQueue() {}
    vector<Event> eq;
};
#endif
