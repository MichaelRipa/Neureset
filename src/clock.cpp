#include "clock.h"

int Clock::getTime() {
  return time;
}

void Clock::tick() {
  time += 1;
}
