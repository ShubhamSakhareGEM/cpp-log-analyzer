#include "Analyzer.h"
#include <iostream>
#include <unordered_map>
#include <algorithm> 
#include <iomanip>

void Analyzer::detectTimingAnomalies(const std::vector<LogEntry>& entries, double thresholdSeconds) {
    std::unordered_map<std::string, std::vector<LogEntry>> threadLogs;

    //grouping by thread
    for (const auto& entry:entries) {
        threadLogs[entry.threadId].push_back(entry);
    }


    std::cout << "\n=== Timing Anomalies (> " << thresholdSeconds << "s gap) ===\n";

    bool found=false;

    for (auto& [threadId, logs] : threadLogs) {
        //sorting logs by timestamp
        std::sort(logs.begin(), logs.end(), [](const LogEntry& a, const LogEntry& b) {
            return a.timestamp < b.timestamp;
        });

        for (size_t i= 1; i < logs.size(); ++i) {
            double gap=logs[i].timestamp - logs[i - 1].timestamp;

            if (gap>thresholdSeconds) {
                found = true;
                std::cout << "Thread: " << threadId
                          << " | Gap: " << std::fixed << std::setprecision(3) << gap << "s"
                          << " | Between: [" << logs[i - 1].message << "]"
                          << " and [" << logs[i].message << "]\n";
            }
        }
    }

    if (!found) {
        std::cout << "No anomalies detected.\n";
    }
}