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
    // std::string messageToFilter = "AFEXDU"; // QC
    std::string stock;
    unsigned count = 0;
    char message[64];
    time_t start;
public:
    Reader() = default;
    Reader(const std::string &fileName, const std::string &stock);
    Reader(const std::string &_stock);
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
