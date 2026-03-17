#include "Parser.h"
#include <sstream>
#include <iostream>
#include <stdexcept>

bool Parser::parseLine(const std::string& line, LogEntry& entry) {
    std::stringstream ss(line);
    std::string timestampStr, threadId, level, module;


    if (!(std::getline(ss, timestampStr, ']') &&
          std::getline(ss, threadId, ']') &&
          std::getline(ss, level, ']') &&
          std::getline(ss, module, ']'))) {
        return false;
    }

    try {
        auto cleanField=[](std::string s) -> std::string {
            size_t start=s.find_first_not_of(" [");
            size_t end =s.find_last_not_of(" ");
            if (start==std::string::npos) return "";
            return s.substr(start, end - start + 1);
        };

        std::string cleanTimestamp= cleanField(timestampStr);
        std::string cleanThreadId= cleanField(threadId);
        std::string cleanLevel=cleanField(level);
        std::string cleanModule=cleanField(module);

        entry.timestamp = std::stod(cleanTimestamp);
        if (entry.timestamp < 0) {
            std::cerr << "Skipping line due to negative timestamp: " << line << "\n";
            return false;
        }
        entry.threadId = cleanThreadId;
        entry.level = cleanLevel;
        entry.module = cleanModule;

        std::string message;
        std::getline(ss, message);
        entry.message = cleanField(message);

        return true;
    } catch (const std::invalid_argument&) {
        std::cerr << "Skipping line due to invalid timestamp: " << line << "\n";
        return false;
    } catch (const std::out_of_range&) {
        std::cerr << "Skipping line due to out-of-range timestamp: " << line << "\n";
        return false;
    }
}