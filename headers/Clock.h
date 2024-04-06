#ifndef CLOCK_H
#define CLOCK_H
    
class Clock {
  public:
    static Clock& getInstance() {
      static Clock instance;
      return instance;
    }
    Clock(Clock const&) = delete;
    void operator=(Clock const&) = delete;
    int getTime();
    void tick();
  private:
    Clock() {}
    int time = 0;
};
#endif
