/*
** NOTE: **

CANNOT have Session variables, must be pointers! This is not allowed for objects
inheriting QObject and will unfortunately break everything.
 */

#pragma once
#include <vector>
#include "session.h"

class PCInterface {
public:
    PCInterface();
    ~PCInterface();
    void uploadData(const std::vector<Session*> sessions);
    void displaySessionLogs() const;
private:
    std::vector<Session*> sessionLogs;
};
