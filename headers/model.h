/*
model.h:
Serves as the model in the MVC paradigm and contains all of the program's business logic,
such as any state that the controller needs to grab when rendering the UI.
*/

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <event-queue.h>
#include <event.h>
#include <neureset-device.h>
#include <eeg-headset.h>

class Model: public QObject
{
Q_OBJECT

public:
    Model(int numSites);
    ~Model();

    void stateChanged();

    NeuresetDevice* getNeuresetDevice();
    EEGHeadset* getEEGHeadset();

signals:
    void modelChanged();


private:
    static int handleEventsFrequency; // How often to handle events in queue, in ms

    NeuresetDevice* neuresetDevice;
    EEGHeadset* eegHeadset;

    QList<Event*> events;
    // EventQueue* eventQueue;  <--- Do we really need an eventsQueue class? Otherwise just list is simpler

    QTimer* handleEventsTimer; // Timer for events handling

private slots:
    // Events handler. called every handleEventsFrequency using Qt slots timer callback
    void handleEvents();
};

#endif // MODEL_H
