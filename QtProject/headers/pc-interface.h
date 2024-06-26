/*
** NOTE: **

CANNOT have Session variables, must be pointers! This is not allowed for objects
inheriting QObject and will unfortunately break everything.
 */

#pragma once
#include <vector>
#include "session.h"
#include "pc.h"
#include "session-log.h"

class PCInterface {
public:
    PCInterface();
    ~PCInterface();
    void uploadData(std::vector<Session*> sessions);
    std::vector<SessionLog> loadAllSessionLogs();
private:
    std::vector<Session*> sessionLogs;
    PC* pc;
};
