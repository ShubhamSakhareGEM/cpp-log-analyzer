#include "Analyzer.h"
#include <iostream>
#include <iomanip>

Analyzer::Analyzer(const std::vector<LogEntry>& logs) : logData(logs) {}

void Analyzer::printErrorSummary() const {
    std::unordered_map<std::string, int> errorCountsByModule;

    for (const auto& log : logData) {
        if (log.level=="ERROR" || log.level=="FATAL") {
            errorCountsByModule[log.moduleName]++;
        }
    }

    
    std::cout << "\n--- ERROR SUMMARY BY MODULE ---\n";
    if (errorCountsByModule.empty()) {
        std::cout << "No errors found. System stable.\n";
        return;
    }
    
    for (const auto& pair : errorCountsByModule) {
        std::cout << "Module [" << pair.first << "] : " << pair.second << " faults\n";
    }
}

void Analyzer::detectTimingAnomalies(double maxAllowedGapSeconds) const {
    std::cout << "\n--- TIMING ANOMALY REPORT (>" << maxAllowedGapSeconds << "s gap) ---\n";
    
    //grouping logs by thread
    std::unordered_map<std::string, std::vector<LogEntry>> logsByThread;
    for (const auto& log : logData) {
        logsByThread[log.threadId].push_back(log);
    }

    bool anomalyFound = false;
    for (const auto& pair : logsByThread) {
        const auto& threadLogs = pair.second;
        for (size_t i = 1; i < threadLogs.size(); ++i) {
            double gap = threadLogs[i].timestamp - threadLogs[i-1].timestamp;
            if (gap > maxAllowedGapSeconds) {
                anomalyFound = true;
                std::cout << "HANG DETECTED in Thread [" << pair.first << "]: Gap of " 
                          << std::fixed << std::setprecision(3) << gap << " seconds.\n"
                          << "  Between: " << threadLogs[i-1].message << "\n"
                          << "  And:     " << threadLogs[i].message << "\n\n";
            }
        }
    }
    if (!anomalyFound) std::cout << "No timing anomalies detected.\n";
}