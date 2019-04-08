#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <sstream> // ostringstream
#include <unordered_map>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>
#include "utility.hpp"

class Parser{
    private:
        std::ifstream inFile;
        std::ofstream outFile;
        time_t start;
        unsigned count;
        char message[64];
    public:
        Parser(const std::string &inFileName, const std::string &outFileName);
        void writeChunk(const std::string &type);
        void writeMessage(const std::string &str);
        void closeStreams();
        void process();
        void readMessage(const long &size);
        void convertMessage(const char &key);
        void printProgress(void);
};

#endif
