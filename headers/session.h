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


class Session: public QObject
{
Q_OBJECT

public:
    Session(int numSites);
    ~Session();

    void calculateBaseline();
    void applyTreatment();
    void saveSessionData();

    int getElaspedTime();
    float getProgress();


private:
    static int nextID;

    int ID;
    int numSites;
    double startTime;
    double endTime;
    QElapsedTimer elapsedTimer;  // Session keeps track of time elapsed on its own

    QTimer* notifyModelTimer;  // Timer used to recurrently tell neureset device the state has been updated
    int notifyModelFreq = 1000; // in ms

    int nextSiteToTreat;

    // before and after dominant frequenices for each site
    std::vector<float> baselineFrequenciesBefore;
    std::vector<float> baselineFrequenciesAfter;

private slots:
    void notifyModel();
};
