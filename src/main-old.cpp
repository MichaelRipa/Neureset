#include <atomic>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "clock.h"
#include "event.h"
#include "event-queue.h"
#include "globals.h"

using namespace std;

atomic<bool> simulateNeuroset(true);

//void signalHandler(int signal) {
//  if (signal == SIGINT) {
//    simulateNeuroset = false;
//  }
//}

//int main(int argc, char* argv[]) {
  
//  // TODO: Update for command line arguments to specify a use scenario
//  if (argc < 2) {
//    cout << "Usage: " << argv[0] << " <N> (0 < N < 8)" << endl;
//    return 1;
//  }
  
//  int scenario = atoi(argv[1]);
  
//  signal(SIGINT, signalHandler);

//  // Initialize components
//  EventQueue& eventQueue = EventQueue::getInstance();
//  Clock& clock = Clock::getInstance();

//  cout << "\n\nNeuroset Simulation beginning!" << endl;
//  cout << "Press CTRL-C to stop\n\n" << endl;

//  int simulationDuration = 0;
//  while (simulateNeuroset) {
//    clock.tick();
//    if (clock.getTime() % TICKS_PER_SECOND == 0) {
//      ++simulationDuration;
//    }
//    vector<Event> events = eventQueue.getEventsForTime(clock.getTime());
//    for (auto & event : events) {
//      break;
//    }

//    // Run specified test scenario
//    switch (scenario) {
//      case 1:
//        break;
//      case 2:
//        break;
//      case 3:
//        break;
//      case 4:
//        break;
//      case 5:
//        break;
//      case 6:
//        break;
//      case 7:
//        break;

//    }

//  }
  
//  cout << "\nNeuroset Simulation stopped by CTRL-C!" << endl;
//  cout << "Deallocating memory" << endl;

//  return 0;

//}

//addEvent(baselineFrequencyComp, 1min)

//handleEvents():
//    Go through each event. If ready to run, remove from vector and run the callback computeBaselineFreq()

