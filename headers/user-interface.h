#pragma once
#include "interface.h"

class UserInterface : public Interface {
public:
    UserInterface();
    ~UserInterface();
    void displayMenu() override;
    void updateTimer() override;
    void updateProgress() override;
private:
    int currentMenu;
    double timer;
    double progressIndicator;
};
