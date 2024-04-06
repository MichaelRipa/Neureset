#include "EventQueue.h"
#include <algorithm>
using namespace std;

void EventQueue::addEvent(const Event& event) {
  eq.push_back(event);
}

vector<Event> EventQueue::getEventsForTime(int time) {
  vector<Event> returnEvents;
  // Uses predicate to filter events matching the current time
  auto it = remove_if(
                      eq.begin(),
                      eq.end(),
                      [&returnEvents, time](const Event& event) {
                        bool isTargetTime = (event.getTime() == time);
                        if (isTargetTime) {
                          returnEvents.push_back(event);
                        }
                        return isTargetTime;
                      });
  // The returned iterator contains the elements to remove, and can be passed directly to `.erase()`
  eq.erase(it, eq.end());
  return returnEvents;
}
