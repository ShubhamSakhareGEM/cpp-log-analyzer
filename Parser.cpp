#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

LogEntry Parser::parseLine(const std::string& line) {
    LogEntry entry;
    //state machine
    size_t pos=0;
    std::vector<std::string> fields;
    
    for (int i=0; i< 4; ++i) {
        size_t start =line.find('[', pos);
        size_t end =line.find(']', start);
        if (start!= std::string::npos && end!=std::string::npos) {
            fields.push_back(line.substr(start + 1, end - start - 1));
            pos= end + 1;
        } else {
            return entry; // if parsing fails, return empty entry
        }
    }

    //assigning fiels
    if (fields.size() == 4) {
        entry.timestamp = std::stod(fields[0]);
        entry.level = fields[1];
        entry.threadId = fields[2];
        entry.moduleName = fields[3];
        
        
        size_t msgStart = line.find_first_not_of(" \t", pos);
        if (msgStart != std::string::npos) {
            entry.message = line.substr(msgStart);
        }
    }
    return entry;
}

std::vector<LogEntry> Parser::parseFile(const std::string& filepath) {
    std::vector<LogEntry> logs;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return logs;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        LogEntry parsedEntry = parseLine(line);
        if (!parsedEntry.level.empty()) {
            logs.push_back(parsedEntry);
        }
    }
    return logs;
}