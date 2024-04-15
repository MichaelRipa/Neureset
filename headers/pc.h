#pragma once
#include "session.h"
#include "session-log.h"
#include <vector>

class PC {
public:
    PC();
    ~PC();
    void uploadData(std::vector<Session*> sessions);
    std::vector<SessionLog> loadSessionLogs();
private:
    std::string PC_FILENAME = "session-logs.csv"; // TODO: Add to globals.h
    bool fileExists(std::string filename);
};
