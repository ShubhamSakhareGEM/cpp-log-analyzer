#ifndef ANALYZER_H
#define ANALYZER_H
#include "LogEntry.h"
#include <vector>
#include <unordered_map>

class Analyzer {
public:
    Analyzer(const std::vector<LogEntry>& logs);

    void printErrorSummary() const;
    void detectTimingAnomalies(double maxAllowedGapSeconds) const;

private:
    std::vector<LogEntry> logData;
};


#endif