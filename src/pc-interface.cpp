#include "pc-interface.h"

PCInterface::PCInterface() {
  pc = new PC();
}

PCInterface::~PCInterface() {
  delete pc;
}

void PCInterface::uploadData(std::vector<Session*> sessions) {
    // Implementation for uploading data
    pc->uploadData(sessions);
}

void PCInterface::displaySessionLogs() const {
    // Implementation for displaying session logs
   // for (const auto& session : sessionLogs) {
        // Display session details
   // }
}
