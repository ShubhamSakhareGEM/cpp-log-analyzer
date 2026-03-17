#ifndef PARSER_H
#define PARSER_H

#include "LogEntry.h"
#include <vector>
#include <string>

class Parser {
public:
    // to parse log entries and return vector
    static std::vector<LogEntry> parseFile(const std::string& filepath);

    
private:
    //function to parse a single line
    static LogEntry parseLine(const std::string& line);
};

#endif