#ifndef WRITER_H_
#define WRITER_H_

#include <iostream>
#include <string>
#include <fstream>

class Writer{
    std::string fileName;
    std::ofstream file;

    public:
    Writer(const std::string& fileName);
    Writer() = default;
    ~Writer();
    void writeLine(std::string stringToWrite);
    std::string getFileName(void) const;
};

#endif
