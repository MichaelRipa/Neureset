/* Model class (following the MVC paradigm) */

#include "model.h"


Model* Model::_instance = 0;

Model* Model::Instance()
{
    if (_instance == 0) {
        _instance = new Model();
    }
    return _instance;
}

void Model::addToEventQueue(Event::EventType eventType, int time)
{
    Event* event = new Event(eventType, elapsedTimer.elapsed() + time);
    eventQueue.push_back(event);
}

int Model::handleEventsFrequency = 100;

Model::Model()
    : eventLoopTimer(new QTimer(this))
{

    elapsedTimer.start();

    neuresetDevice = new NeuresetDevice();
    eegHeadset = new EEGHeadset(NUM_SITES);

    neuresetDevice->setEEGHeadset(eegHeadset);
    eegHeadset->setNeuresetDevice(neuresetDevice);

    // Set up callback connections
    connect(eventLoopTimer, SIGNAL(timeout()), this, SLOT(eventLoop()));

    eventLoopTimer->start(handleEventsFrequency);
}


Model::~Model()
{
}

void Model::eventLoop()
{
    int time = elapsedTimer.elapsed();

    // TODO - check latest events, see if they must modify / cancel any previous event

    handleReadyEvents();

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


void Model::handleReadyEvents() {
    int time = elapsedTimer.elapsed();

    std::vector<Event*> readyEvents;

    for (int i = eventQueue.size() - 1; i >= 0; --i) {
        if (eventQueue[i]->getTime() < time) {
            readyEvents.push_back(eventQueue[i]);
            eventQueue.pop_back();
        }
    }

    for (int i = readyEvents.size() - 1; i >= 0; --i)
        handleSingleEvent(readyEvents[i]);
}

// All individual event handling can go here
void Model::handleSingleEvent(Event *event)
{
    if (event->getType() == Event::EventType::CalculateBaselineAverages) {
        neuresetDevice->calculateBaselineAverages();
    }

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


