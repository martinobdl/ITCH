#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utility.hpp"

class Parser{
    private:
        std::ifstream inFile;
        std::ofstream outFile;
        unsigned count;
        std::unordered_map<char, std::vector<std::string>> format_map;
        time_t start;
    public:
        Parser(const std::string &inFileName, const std::string &outFileName);
        void writeChunk(const char *type);
        void writeMessage(const std::string &format);
        void closeStreams();
        void process();
};

#endif
