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

int Model::handleEventsFrequency = 300;

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
    handleReadyEvents();

    // If event queue is empty and neureset device is in session, it is ready to run the current stage
    // of its session treatment (e.g computing post treatment baseline frequencies)
    if (eventQueue.size() == 0 && neuresetDevice->getCurrentSessionStatus() == NeuresetDevice::SessionStatus::InProgress) {
        neuresetDevice->runCurrentSessionStage();
    }

}


void Model::addToEventQueue(Event::EventType eventType, int time)
{
    Event* event = new Event(eventType, elapsedTimer.elapsed() + time);
    eventQueue.push_back(event);
    updateEventQueueBasedOnEvent(event);
}


void Model::updateEventQueueBasedOnEvent(Event *event) {
    // Only pausing related events cancel out other events when added to the queue.
    if (!(event->getType() == Event::EventType::UserPausedSession ||
          event->getType() == Event::EventType::connectionLossPausedSession))
        return;
    // Remove in session treatment related events
    for (int i = eventQueue.size() - 1; i >= 0; --i) {
        if (eventQueue[i]->getType() == Event::EventType::CalculateBaselineAverages ||
            eventQueue[i]->getType() == Event::EventType::CalculateFrequencyAtCurrentSite ||
            eventQueue[i]->getType() == Event::EventType::ApplyTreatmentToCurrentSite)
        {
            Event* removedEvent = eventQueue[i];
            eventQueue.erase(eventQueue.begin() + i);
            delete removedEvent;
        }
    }
}

void Model::handleReadyEvents() {
    int time = elapsedTimer.elapsed();

    std::vector<Event*> readyEvents;

    for (int i = eventQueue.size() - 1; i >= 0; --i) {
        if (eventQueue[i]->getTime() < time) {
            readyEvents.push_back(eventQueue[i]);
            eventQueue.erase(eventQueue.begin() + i);
        }
    }

    for (int i = readyEvents.size() - 1; i >= 0; --i)
        handleSingleEvent(readyEvents[i]);
}

// All individual event handling can go here
void Model::handleSingleEvent(Event *event)
{
    qDebug("Handling single event.");
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


