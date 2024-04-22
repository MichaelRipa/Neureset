#include "pc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>

PC::PC() {}

PC::~PC() {}

std::string getHomeDirectory() {
    const char* homedir = getenv("HOME");
    if (!homedir) {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd) {
            homedir = pwd->pw_dir;
        }
    }
    return std::string(homedir ? homedir : ".");
}

bool PC::fileExists(std::string filename) {
  // Simple helper function which checks whether the session log file has already been written
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

void PC::uploadData(std::vector<Session*> sessions) {

  std::string homeDir = getHomeDirectory(); // Get the home directory path
  std::string fullPath = homeDir + "/" + PC_FILENAME.toStdString(); // Append the filename to the home directory path

  std::ofstream file;

  // Check if the file exists and has content
  bool exists = fileExists(fullPath);
  bool writeHeader = !exists || std::ifstream(fullPath).peek() == std::ifstream::traits_type::eof();

  // Open the file in append mode
  file.open(fullPath, std::ios::app);

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
    std::string homeDir = getHomeDirectory();
    std::string fullPath = homeDir + "/" + PC_FILENAME.toStdString();

    std::ifstream file(fullPath);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fullPath << std::endl;
        qDebug() << "Failed to open file";
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
        log.startTime = QDateTime::fromString(QString::fromStdString(cell).trimmed(), "yyyy-MM-dd.hh:mm");
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
