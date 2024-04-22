#ifndef EVENT_H
#define EVENT_H

class Event {
  public:
    enum class EventType {
        CalculateBaselineAverages, CalculateFrequencyAtCurrentSite, ApplyTreatmentToCurrentSite,
        EndTreatmentCurrentSite, UserPausedSession, ConnectionLossPausedSession
    };

    Event(EventType type, int time);

    EventType getType();
    int getTime() const;

  private:
    EventType type;
    int time;
};

#endif 
