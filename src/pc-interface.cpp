#include "pc-interface.h"

PCInterface::PCInterface() {}

PCInterface::~PCInterface() {}

void PCInterface::uploadData(const std::vector<Session*> sessions) {
    // Implementation for uploading data
    sessionLogs = sessions;
}

void PCInterface::displaySessionLogs() const {
    // Implementation for displaying session logs
   // for (const auto& session : sessionLogs) {
        // Display session details
   // }
}
