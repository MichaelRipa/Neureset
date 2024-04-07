#pragma once
#include "pc-interface.h"

class PC {
public:
    PC();
    ~PC();
    void uploadData();
    void displaySessionLogs();
private:
    PCInterface pcInterface;
};
