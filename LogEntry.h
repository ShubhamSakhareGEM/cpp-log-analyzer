#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <string>

// to show single parsed line from the log file
struct LogEntry {
    double timestamp;
    std::string level;
    std::string threadId;
    std::string moduleName;
    std::string message;
};


#endif