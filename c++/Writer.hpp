#ifndef WRITER_H_
#define WRITER_H_

#include <iostream>
#include <string>
#include <fstream>

class Writer{

    std::string fileName="";
    std::ofstream file;

    public:
    Writer(const std::string& fileName);
    ~Writer();
    void writeLine(std::string stringToWrite);
};
#endif
