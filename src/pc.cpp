#include "pc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QString>
#include <QDateTime>
#include <sys/stat.h>

PC::PC() {}

PC::~PC() {}

bool PC::fileExists(std::string filename) {
  // Simple helper function which checks whether the session log file has already been written
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

void PC::uploadData(std::vector<Session*> sessions) {
  std::ofstream file;

  // Check if the file exists and has content
  bool exists = fileExists(PC_FILENAME);
  bool writeHeader = !exists || std::ifstream(PC_FILENAME).peek() == std::ifstream::traits_type::eof();

  // Open the file in append mode
  file.open(PC_FILENAME, std::ios::app);

  if (writeHeader) {
      // Assuming all sessions have the same number of sites (for header purposes)
      int numSites = sessions.empty() ? 0 : sessions.front()->getNumSites();

      // Write the header
      file << "id, Date";
      for (int i = 1; i <= numSites; ++i) {
          file << ", before_site" << i << ", after_site" << i;
      }
      file << "\n";
  }

  // Iterate over each session and write the data
  for (size_t i = 0; i < sessions.size(); ++i) {
      const auto session = sessions[i];
      file << i + 1 << ", " << session->getStartTime().toString("yyyy-MM-dd.hh:mm").toStdString();

      const auto beforeFrequencies = session->getBaselineFrequenciesBefore();
      const auto afterFrequencies = session->getBaselineFrequenciesAfter();

      // Ensure we have frequencies for all sites
      for (int j = 0; j < (int)beforeFrequencies.size(); ++j) {
          float before = j < beforeFrequencies.size() ? beforeFrequencies[j] : 0.0f;
          float after = j < afterFrequencies.size() ? afterFrequencies[j] : 0.0f;
          file << ", " << before << ", " << after;
      }
      file << "\n";
  }

  // Close the file
  file.close();
} 

std::vector<SessionLog> PC::loadSessionLogs() {
    std::vector<SessionLog> logs;
    std::string filename = PC_FILENAME;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return logs;
    }

    std::string line;
    getline(file, line); // Skip the header

    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string cell;
        SessionLog log;

        // Read ID
        getline(ss, cell, ',');
        log.id = std::stoi(cell);

        // Read Date and Time
        getline(ss, cell, ',');
        log.startTime = QDateTime::fromString(QString::fromStdString(cell), "yyyy-MM-dd.hh:mm");

        // Read before and after frequencies
        while (getline(ss, cell, ',')) {
            float frequency = std::stof(cell);
            log.beforeFrequencies.push_back(frequency); // Assumes even distribution of before and after frequencies

            if (getline(ss, cell, ',')) {
                frequency = std::stof(cell);
                log.afterFrequencies.push_back(frequency);
            }
        }

        logs.push_back(log);
    }

    file.close();
    return logs;
}
