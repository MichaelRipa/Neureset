#include "session.h"
#include "model.h"


int Session::nextID = 0;


Session::Session(int numSites, QDateTime startTime)
    : ID(nextID), currentStage(Stage::computePreTreatmentBaselines), numSites(numSites),
      startTime(startTime), running(true), treatmentCurrentSite(1)
{

    Session::nextID++;

    // Init baseline frequencies to default, not-yet-computed values
    for(int i = 0; i < numSites; ++i) {
        baselineFrequenciesBefore.push_back(-1);
        baselineFrequenciesAfter.push_back(-1);
    }
}

Session::~Session()
{}

void Session::setStage(Stage stage)
{
    currentStage = stage;
}

void Session::setTreatmentCurrentSite(int site)
{
    treatmentCurrentSite = site;
}


Session::Stage Session::getStage()
{
    return currentStage;
}

void Session::calculateBaseline() {
    // Implementation for calculating baseline
}

void Session::applyTreatment() {
    // Implementation for applying treatment
}

void Session::saveSessionData() {
    // Implementation for saving session data
}

bool Session::isRunning()
{
    return running;
}

int Session::getEstimatedTimeLeft() {
    int timeLeft = 0;

    // Post treatment baseline frequency calculations
    timeLeft += TIME_TO_COMPUTE_FREQUENCY;

    // Estimated time to apply treatments
    if (currentStage != Stage::computePostTreatmentBaselines) {
        timeLeft += (TIME_TO_COMPUTE_FREQUENCY + SITE_TREATMENT_DURATION) * (numSites - treatmentCurrentSite);
    }
    // Pre-treatment baseline frequency calculations
    if (currentStage == Stage::computePreTreatmentBaselines)
            timeLeft += TIME_TO_COMPUTE_FREQUENCY;

    return timeLeft / 1000;
}


float Session::getProgress()
{
    if (currentStage == Stage::computePreTreatmentBaselines)
        return 0;
    else if (currentStage == Stage::ApplyTreatmentToSites) {
        int numSitesCompleted = treatmentCurrentSite - 1;
        if (numSitesCompleted <= 1)
                numSitesCompleted = 1;
        return ((float)numSitesCompleted) / (float) numSites;
    }
    else
        return 99;
}

int Session::getNumSites() {
    return numSites;
}

int Session::getTreatmentCurrentSite()
{
    return treatmentCurrentSite;
}

QDateTime Session::getStartTime() {
  return startTime;
}

std::vector<float> Session::getBaselineFrequenciesBefore() {
  return baselineFrequenciesBefore;
}

std::vector<float> Session::getBaselineFrequenciesAfter() {
  return baselineFrequenciesAfter;
}

void Session::setBaselineFrequenciesBefore(std::vector<float> freqs) {
  baselineFrequenciesBefore = freqs;
}

void Session::setBaselineFrequenciesAfter(std::vector<float> freqs) {
  baselineFrequenciesAfter = freqs;
}
