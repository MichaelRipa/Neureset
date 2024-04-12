/* Model class (following the MVC paradigm) */

#include "model.h"


int Model::handleEventsFrequency = 100;


Model::Model(int numSites)
    : handleEventsTimer(new QTimer(this))
{

    timeElapsed.start();

    eegHeadset = new EEGHeadset(this, numSites);
    neuresetDevice = new NeuresetDevice(this, eegHeadset);

    // Set up callback connections
    connect(handleEventsTimer, SIGNAL(timeout()), this, SLOT(handleEvents()));

    handleEventsTimer->start(handleEventsFrequency);
}


Model::~Model()
{
}

void Model::handleEvents()
{
    int time = timeElapsed.elapsed();

    // Get events ready to handle
    // helper func
    // Handle those events


//    qDebug("Handling events.");
//    vector<Event> returnEvents;
//    // Uses predicate to filter events matching the current time
//    auto it = remove_if(
//                      eventQueue.begin(),
//                      eventQueue.end(),
//                      [&returnEvents, time](const Event& event) {
//                        bool isTargetTime = (event.getTime() == time);
//                        if (isTargetTime) {
//                          returnEvents.push_back(event);
//                        }
//                        return isTargetTime;
//                      });
//    // The returned iterator contains the elements to remove, and can be passed directly to `.erase()`
//    eventQueue.erase(it, eventQueue.end());
//    return returnEvents;
}


void Model::addToEventQueue(Event* event) {
    eventQueue.push_back(event);
}

// Called by anywhere in business logic whenever any model state changes. The UI
// picks this up and rerenders.
void Model::stateChanged() {
    emit modelChanged();
}


NeuresetDevice *Model::getNeuresetDevice()
{
    return neuresetDevice;
}

EEGHeadset *Model::getEEGHeadset()
{
    return eegHeadset;
}


