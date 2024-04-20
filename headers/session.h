/*
Session.h:
Serves primarily as a container class the neureset device stores information to as it administrates
treatment for a particular session.
*/

#pragma once

#include <vector>
#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QDateTime>

class Session: public QObject
{
Q_OBJECT

public:

    enum class Stage { computePreTreatmentBaselines, ApplyTreatmentToSites, computePostTreatmentBaselines };

    Session(int numSites, QDateTime startTime);
    ~Session();

    void calculateBaseline();
    void applyTreatment();
    void saveSessionData();

    void startTimer();
    void pauseTimer();

    void setStage(Stage stage);
    void setTreatmentCurrentSite(int site);

    bool isRunning();
    Stage getStage();
    int getElapsedTime();
    float getProgress();
    int getNumSites();
    int getTreatmentCurrentSite();
    QDateTime getStartTime();
    std::vector<float> getBaselineFrequenciesBefore();
    std::vector<float> getBaselineFrequenciesAfter();
    void setBaselineFrequenciesBefore(std::vector<float> freqs);
    void setBaselineFrequenciesAfter(std::vector<float> freqs);

private:
    static int nextID;

    int ID;
    int numSites;

    // Keeps track of the current stage of treatment
    Stage currentStage;

    QDateTime startTime;
    int elapsedTime;
    double endTime; // TODO: This likely will change

    QTimer* updateElapsedTimeTimer;  // Timer used to recurrently update session time
    int updateTimeFreq = 1000; // in ms

    // Keeps track of the time since the session was last started
    // (either for first time or since paused / disconnected).
    // Cannot be stopped, only restarted, hence need for elapsedTime int
    QElapsedTimer timeSinceLastStart;
    int timeBeforeLastStart;

    int treatmentCurrentSite;  // Current site that treatment is being applied to (or will be applied to next)
    bool running;  // True iff treatment currently being applied

    // before and after dominant frequenices for each site
    std::vector<float> baselineFrequenciesBefore;
    std::vector<float> baselineFrequenciesAfter;

private slots:
    void updateElapsedTime();
};
