#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include "Message.hpp"
#include <string>

class Reader{
    private:
    std::string fileName;
    std::ifstream file;
    std::string messageToFilter = "AFEXDU"; // PQ
    std::string stock;
    bool finished = 0;
    public:
    Reader(const std::string &fileName, const std::string &stock);
    std::string getLine(void);
    Message createMessage(void); 
    bool eof(){
        return finished;
    }
};

#endif
