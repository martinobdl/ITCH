#include "Reader.hpp"

Reader::Reader(const std::string &_fileName): 
    fileName(_fileName){
        file.open(fileName);
        if(!file.is_open()){
            std::cerr << "Can't open input file " << fileName << std::endl;
            }
        else{
            std::cout << "Opened " << fileName << " to read ITCH 5.0. messages." << std::endl;
        }
    }

std::string Reader::getLine(void){
    std::string message;
    std::getline(file, message);
    finished = file.eof();
    if(messageToFilter.find(message[0])){
        return message;
    }
    else{
        return std::string();
    }

}
