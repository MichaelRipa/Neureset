/*
model.h:
Serves as the model in the MVC paradigm and contains all of the program's business logic,
such as any state that the controller needs to grab when rendering the UI.
The model also follows the singleton design pattern as only one should ever be instantiated
and it allows for easy access from the model's components.
*/

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <event.h>
#include <neureset-device.h>
#include <eeg-headset.h>
#include <vector>
#include <QElapsedTimer>
#include <globals.h>


class Model: public QObject
{
Q_OBJECT

public:
    static Model* Instance();

    void addToEventQueue(Event::EventType eventType, int time);
    void clearEventType(Event::EventType eventType);
    void clearTreatmentEvents();
    void clearAllEvents();

    void stateChanged();


    NeuresetDevice* getNeuresetDevice();
    EEGHeadset* getEEGHeadset();

signals:
    void modelChanged();


private:
    Model();
    ~Model();

    // If current event is a pause or disconnect, remove any current session
    // treatment events in queue (all assumed non pause/disconnect events assumed to be).
    void updateEventQueueBasedOnEvent(Event* event);

    static Model* _instance;

    static int handleEventsFrequency; // How often to handle events in queue, in ms


    void handleReadyEvents(); // Gets events ready to handle
    void handleSingleEvent(Event* event);


    QElapsedTimer elapsedTimer; // Keeps track of time since program start

    NeuresetDevice* neuresetDevice;
    EEGHeadset* eegHeadset;

    std::vector<Event*> eventQueue;

    QTimer* eventLoopTimer; // Timer for events handling

private slots:
    // Events handler. called every handleEventsFrequency using Qt slots timer callback
    void eventLoop();
};

#endif // MODEL_H
