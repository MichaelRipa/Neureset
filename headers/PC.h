#pragma once
#include "PCInterface.h"

class PC {
public:
    PC();
    ~PC();
    void uploadData();
    void displaySessionLogs();
private:
    PCInterface pcInterface;
};
