#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <inttypes.h> // PRIux
#include <cstring>
#include <algorithm> // min
#include <cmath> // sqrt
#include <Message.hpp>
#include <Writer.hpp>

class Reader{
private:
    std::string fileName;
    std::ifstream file;
    // std::string messageToFilter = "AFEXDU"; // QC
    std::string stock;
    unsigned count = 0;
    char message[64];
    bool goodFile = 0;
    time_t start;
    // bool debug = 0;
    // Writer parserWriter;
public:
    Reader(const std::string &fileName, const std::string &stock);
    Reader(const std::string &_stock);
    bool isGood(void) const;
    virtual ~Reader();
    Message createMessage(void);
    bool eof();
    void printProgress(void);
    virtual void readBytesIntoMessage(const long &size);
    virtual void skipBytes(const long &size);
    void setMessage(const char* str);
    virtual char getKey(void);
    std::string getFileName(void) const;
    std::string getStock(void) const;
};

#endif
