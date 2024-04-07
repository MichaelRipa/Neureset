#pragma once
#include <vector>
#include "session.h"

class PCInterface {
public:
    PCInterface();
    ~PCInterface();
    void uploadData(const std::vector<Session>& sessions);
    void displaySessionLogs() const;
private:
    std::vector<Session> sessionLogs;
};
