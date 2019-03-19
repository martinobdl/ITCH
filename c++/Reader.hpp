#ifndef READER_H_
#define READER_H_

#include<fstream>
#include<iostream>

class Reader{
    private:
    std::string fileName;
    std::ifstream file;
    std::string messageToFilter = "AFEXDUPQ";
    bool finished = 0;
    public:
    Reader(const std::string &fileName);
    std::string getLine(void);
    bool eof(){
        return finished;
    }
};

#endif
