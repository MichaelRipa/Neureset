#pragma once
#include "session.h"
#include "session-log.h"
#include "globals.h"
#include <vector>

class PC {
public:
    PC();
    ~PC();
    void uploadData(std::vector<Session*> sessions);
    std::vector<SessionLog> loadSessionLogs();
private:
    bool fileExists(std::string filename);
};
