/* Model class (following the MVC paradigm) */

#include "model.h"


int Model::handleEventsFrequency = 100;


Model::Model(int numSites)
    : handleEventsTimer(new QTimer(this))
{

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
    qDebug("Handling events.");
}

void Model::addToEventQueue(Event *event) {
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


