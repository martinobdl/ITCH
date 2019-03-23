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

Message createMessage(void){
    Message msg();
    std::string typeCell;
    std::getline(file, typeCell, ',');
    msg.setType(typeCell);
    std::string cell;
    std::getline(file, cell, ',');
    std::getline(file, cell, ',');
    std::getline(file, cell, ',');
    msg.setTimeStamp(std::stol(cell));
    std::getline(file, cell, ',');
    if(typeCell=='U'){
        msg.setOldId(std::stod(cell));
    }
    else{
        msg.setId(std::stod(cell));
    }
    std::getline(file, cell, ',');
    if(typeCell=='A' || typeCell =='F'){
        
    }

}



