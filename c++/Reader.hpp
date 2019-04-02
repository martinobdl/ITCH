#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include "Message.hpp"

class Reader{
    private:
    std::string fileName;
    std::ifstream file;
    std::string messageToFilter = "AFEXDU"; // PQ
    std::string stock;
    bool finished = 0;
    unsigned count = 0;
    time_t start;
    public:
    Reader(const std::string &fileName, const std::string &stock);
    ~Reader();
    std::string getLine(void);
    Message createMessage(void);
    bool eof();
    void printProgress(void);
};

#endif
