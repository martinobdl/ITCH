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

void Reader::printProgress(void){
    count ++;
    if((count % 5000000)==0){
        std::cout << "Processed " << count/1000000 << "Mio messages. " << count/difftime(time(0), start) << " messages per sec." << std::endl;
    }
}

void Reader::readBytes(const long &size){
    file.read(message, size);
}

Message Reader::createMessage(void){
    printProgress();
    Message msg;
    char key;
    file.ignore(2);
    file.get(key);

    if(key=='S'){
        readBytes(11);
    }
    else if(key=='R'){
        readBytes(38);
    }
    else if(key=='H'){
        readBytes(24);
    }
    else if(key=='Y'){
        readBytes(19);
    }
    else if(key=='L'){
        readBytes(25);
    }
    else if(key=='V'){
        readBytes(34);
    }
    else if(key=='W'){
        readBytes(11);
    }
    else if(key=='K'){
        readBytes(27);
    }
    else if(key=='J'){
        readBytes(34);
    }
    else if(key=='h'){
        readBytes(20);
    }
    else if(key=='A'){
        readBytes(35);
        char ticker[9]; strncpy(ticker, message+23, 8); ticker[8] = 0;
        if(strcmp(ticker,stock.c_str())){
            return msg;
        }
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        char direction = message[18];
        uint32_t size = parse_uint32(message+19);
        uint32_t price = parse_uint32(message+31);
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(orderId));
        msg.setSide(static_cast<side_type>(direction == 'S'));
        msg.setRemSize(static_cast<size_type>(size));
        msg.setPrice(static_cast<price_type>(price)/10000);
    }
    else if(key=='F'){
        readBytes(39);
        char ticker[9]; strncpy(ticker, message+23, 8); ticker[8] = 0;
        if(strcmp(ticker,stock.c_str())){
            return msg;
        }
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        char direction = message[18];
        uint32_t size = parse_uint32(message+19);
        uint32_t price = parse_uint32(message+31);
        char mpid[5]; strncpy(mpid, message+35, 4); mpid[4] = 0;
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(orderId));
        msg.setSide(static_cast<side_type>(direction == 'S'));
        msg.setRemSize(static_cast<size_type>(size));
        msg.setPrice(static_cast<price_type>(price)/10000);
    }
    else if(key=='E'){
        readBytes(30);
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        uint32_t execSize = parse_uint32(message+18);
        // uint64_t matchNumber = parse_uint64(message+22);
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(orderId));
        msg.setExecSize(static_cast<size_type>(execSize));
    }
    else if(key=='C'){
        readBytes(35);
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        // uint64_t timeStamp = parse_ts(message+4);
        // uint64_t orderId = parse_uint64(message+10);
        // uint32_t execSize = parse_uint32(message+18);
        // // uint64_t matchNumber = parse_uint64(message+22);
        // char printable = message[30];
        // uint32_t price = parse_uint32(message+31);

        // Check how to use C.

    }
    else if(key=='X'){
        readBytes(22);
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        uint32_t cancSize = parse_uint32(message+18);
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(orderId));
        msg.setCancSize(static_cast<size_type>(cancSize));
    }
    else if(key=='D'){
        readBytes(18);
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t orderId = parse_uint64(message+10);
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(orderId));
    }
    else if(key=='U'){
        readBytes(34);
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        uint64_t timeStamp = parse_ts(message+4);
        uint64_t oldOrderId = parse_uint64(message+10);
        uint64_t newOrderId = parse_uint64(message+18);
        uint32_t newSize = parse_uint32(message+26);
        uint32_t newPrice = parse_uint32(message+30);
        msg.setType(std::string(1,key));
        msg.setTimeStamp(static_cast<time_type>(timeStamp));
        msg.setId(static_cast<id_type>(newOrderId));
        msg.setOldId(static_cast<id_type>(oldOrderId));
        msg.setRemSize(static_cast<size_type>(newSize));
        msg.setPrice(static_cast<price_type>(newPrice)/10000);
    }
    else if(key=='P'){
        readBytes(43);
        char ticker[9]; strncpy(ticker, message+23, 8); ticker[8] = 0;
        if(strcmp(ticker,stock.c_str())){
            return msg;
        }
        // uint16_t locateCode = parse_uint16(message);
        // uint16_t trackingNumb = parse_uint16(message+2);
        // uint64_t timeStamp = parse_ts(message+4);
        // uint64_t orderId = parse_uint64(message+10);
        // char direction = message[18];
        // uint32_t size = parse_uint32(message+19);
        // uint32_t price = parse_uint32(message+31);
        // // uint64_t matchId = parse_uint64(message+35);
        // msg.setType(std::string(1,key));
        // msg.setTimeStamp(static_cast<time_type>(timeStamp));
        // msg.setId(static_cast<id_type>(orderId));
        // msg.setSide(static_cast<side_type>(direction == 'S'));
        // msg.setExecSize(static_cast<size_type>(size));
        // msg.setPrice(static_cast<price_type>(price)/10000);

    }
    else if(key=='Q'){
        readBytes(39);
        // // uint16_t locateCode = parse_uint16(message);
        // // uint16_t trackingNumb = parse_uint16(message+2);
        // uint64_t timeStamp = parse_ts(message+4);
        // uint64_t size = parse_uint64(message+10);
        // char stock[9]; strncpy(stock, message+18, 8); stock[8] = 0;
        // uint32_t price = parse_uint32(message+26);
        // // uint64_t matchId = parse_uint64(message+30);
        // char crossType = message[38];

        // Check how to use Q.

    }
    else if(key=='B'){
        readBytes(18);
    }
    else if(key=='I'){
        readBytes(49);
    }
    else{
        std::cerr << "Type " << key <<" not found @ line: "<< count << std::endl;
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
