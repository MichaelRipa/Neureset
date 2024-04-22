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

std::vector<SessionLog> PCInterface::loadAllSessionLogs() {
  return pc->loadSessionLogs();
}
