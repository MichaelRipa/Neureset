#include "session.h"
#include "model.h"


int Session::nextID = 0;


Session::Session(int numSites, QDateTime startTime)
    : ID(nextID), numSites(numSites), startTime(startTime), endTime(0.0),
       elapsedTime(0), running(true), updateElapsedTimeTimer(new QTimer(this)),
       timeBeforeLastStart(0)

{

    Session::nextID++;

    // Init baseline frequencies to default, not-yet-computed values
    for(int i = 0; i < numSites; ++i) {
        baselineFrequenciesBefore.push_back(-1);
        baselineFrequenciesAfter.push_back(-1);
    }

    updateElapsedTimeTimer->start();
    timeSinceLastStart.start();

    // Set up callback connections
    connect(updateElapsedTimeTimer, SIGNAL(timeout()), this, SLOT(updateElapsedTime()));

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

void Session::setRunning(bool running)
{
    this->running = running;
    timeBeforeLastStart = elapsedTime;
    if (running) {
        timeSinceLastStart.restart();
    }
}

bool Session::isRunning()
{
    return running;
}


float Session::getProgress()
{
    return 0;
}

int Session::getElapsedTime()
{
    return elapsedTime;
}

void Session::updateElapsedTime()
{
    if (running) {
        qDebug("Session running.");
        elapsedTime = timeBeforeLastStart + timeSinceLastStart.elapsed();
        Model::Instance()->modelChanged();
    }
}

