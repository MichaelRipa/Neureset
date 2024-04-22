#ifndef SESSIONLOG_H
#define SESSIONLOG_H

#include <QDateTime>
#include <vector>

struct SessionLog {
    int id;
    QDateTime startTime;
    std::vector<float> beforeFrequencies;
    std::vector<float> afterFrequencies;
};

#endif // SESSIONLOG_H
