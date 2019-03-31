#include "Reader.hpp"

Reader::Reader(const std::string &_fileName, const std::string &_stock):
    fileName(_fileName), stock(_stock){
        file.open(fileName);
        if(!file.is_open()){
            std::cerr << "Can't open input file " << fileName << std::endl;
            }
        else{
            std::cout << "Opened " << fileName << " to read ITCH 5.0. messages." << std::endl;
        }
    start = time(0);
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

Message Reader::createMessage(void){
    Message msg;
    count ++;
    if((count % 5000000)==0){
        std::cout << "Processed " << count/1000000 << "Mio messages. " << count/difftime(time(0), start) << " messages per sec." << std::endl;
    }
    if(!eof()){
        std::string typeCell;
        std::string cell;
        std::getline(file, typeCell, ',');
        if(messageToFilter.find(typeCell)==std::string::npos or typeCell == ""){
            std::getline(file, cell);
            return Message();
        }
        msg.setType(typeCell);
        std::getline(file, cell, ',');
        std::getline(file, cell, ',');
        std::getline(file, cell, ',');
        msg.setTimeStamp(std::stol(cell));
        if(typeCell == "A" || typeCell == "F"){
            std::getline(file, cell, ',');
            msg.setId(std::stol(cell));
            std::getline(file, cell, ',');
            msg.setSide(cell=="S");
            std::getline(file, cell, ',');
            msg.setRemSize(std::stod(cell));
            std::getline(file, cell, ',');
            // check if rigth stock
            if(cell.compare(stock) != 0){
                std::getline(file, cell);
                return Message();
            }
            if(typeCell == "A"){
                std::getline(file, cell);
                msg.setPrice(std::stod(cell));
            }
            if(typeCell == "F"){
                std::getline(file, cell, ',');
                msg.setPrice(std::stod(cell));
                std::getline(file, cell);
            }
        }
        if(typeCell=="U"){
            std::getline(file, cell, ',');
            msg.setOldId(std::stol(cell));
            std::getline(file, cell, ',');
            msg.setId(std::stol(cell));
            std::getline(file, cell, ',');
            msg.setPrice(std::stod(cell));
            std::getline(file, cell);
            msg.setRemSize(std::stod(cell));
        }
        if(typeCell == "D"){
            std::getline(file, cell);
            msg.setId(std::stol(cell));
        }
        if(typeCell == "X"){
            std::getline(file, cell, ',');
            msg.setId(std::stod(cell));
            std::getline(file, cell);
            msg.setCancSize(std::stod(cell));
        }
        if(typeCell == "E"){
            std::getline(file, cell, ',');
            msg.setId(std::stod(cell));
            std::getline(file, cell, ',');
            msg.setExecSize(std::stod(cell));
            std::getline(file, cell);
        }
    }
    return msg;
}

bool Reader::eof(){
    return file.eof();
}

Reader::~Reader(){
    if (file.is_open()){
        file.close();
        std::cout<<"file "<<fileName<<" has been closed"<<std::endl;
        std::cout << "Finished, processed " << count << " messages in " << difftime(time(0),start) << "seconds."  << std::endl;
    }
}
