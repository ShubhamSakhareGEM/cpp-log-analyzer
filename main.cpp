#include "Parser.h"
#include "Analyzer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc<2) {
        std::cerr<<"Usage: ./log_analyzer <path_to_log_file>\n";
        return 1;
    }
    std::string filepath=argv[1];
    std::cout<<"parsing log file: "<<filepath<<"...\n";


    std::vector<LogEntry> logs=Parser::parseFile(filepath);
    
    if (logs.empty()) {
        std::cerr<<"no valid logs parsed. Exiting.\n";
        return 1;
    }

    std::cout<<"successfully parsed " << logs.size() << " log entries.\n";

    Analyzer analyzer(logs);
    
    // running analysis tool
    analyzer.printErrorSummary();
    
    // detecting gaps bigger than 1.5 seconds to simulate real-time OS constraint
    analyzer.detectTimingAnomalies(1.5); 

    return 0;
}