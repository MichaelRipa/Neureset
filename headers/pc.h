#pragma once
#include "pc-interface.h"
#include "session.h"
#include <vector>

class PC {
public:
    PC();
    ~PC();
    void uploadData(std::vector<Session*> sessions);
    void displaySessionLogs();
private:
    PCInterface pcInterface;
    std::string PC_FILENAME = "session-logs.csv"; // TODO: Add to globals.h
    bool fileExists(std::string filename);
};
