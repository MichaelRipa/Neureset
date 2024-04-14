#include "session.h"
#include "model.h"


int Session::nextID = 0;


Session::Session(int numSites)
    : ID(nextID), numSites(numSites), startTime(0.0), endTime(0.0),
      notifyModelTimer(new QTimer(this))

{

    Session::nextID++;

    // Init baseline frequencies to default, not-yet-computed values
    for(int i = 0; i < numSites; ++i) {
        baselineFrequenciesBefore.push_back(-1);
        baselineFrequenciesAfter.push_back(-1);
    }

    elapsedTimer.start();

    notifyModelTimer->start();

    // Set up callback connections
    connect(notifyModelTimer, SIGNAL(timeout()), this, SLOT(notifyModel()));

}


Session::~Session()
{}

void Session::calculateBaseline() {
    // Implementation for calculating baseline
}

void Session::applyTreatment() {
    // Implementation for applying treatment
}

void Session::saveSessionData() {
    // Implementation for saving session data
}

float Session::getProgress()
{
    return 0;
}

int Session::getElaspedTime()
{
    return elapsedTimer.elapsed();
}

void Session::notifyModel()
{
    Model::Instance()->modelChanged();
}

