#pragma once

class Interface {
public:
    virtual void displayMenu() = 0;
    virtual void updateTimer() = 0;
    virtual void updateProgress() = 0;
};
