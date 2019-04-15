#include "Reader.hpp"

Reader::Reader(const std::string &_fileName, const std::string &_stock):
    fileName(_fileName), stock(_stock){
        file.open(fileName);
        if(!file.is_open()){
            std::cerr << "Can't open input file " << fileName << std::endl;
            }
        else{
            std::cout << "Opened " << fileName << " to read ITCH 5.0. messages." << std::endl;
            goodFile = 1;
        }
    start = time(0);
    }

Reader::Reader(const std::string &_stock):
    stock(_stock){}

void Reader::printProgress(void){
    count ++;
    if((count % 5000000)==0){
        std::cout << "Processed " << count/1000000 << "Mio messages. " << count/difftime(time(0), start) << " messages per sec." << std::endl;
    }
}

void Reader::readBytesIntoMessage(const long &size){
    file.read(message, size);
}

void Reader::skipBytes(const long &size){
    file.ignore(size);
}

char Reader::getKey(void){
    char key;
    file.get(key);
    return key;
}

Message Reader::createMessage(void){
    printProgress();
    Message msg;
    skipBytes(2);
    char key = getKey();

    switch(key){

        uint64_t timeStamp;
        uint64_t orderId;
        char direction;
        char ticker[9];
        uint32_t size;
        uint32_t price;
        uint32_t execSize;
        uint32_t cancSize;
        uint64_t oldOrderId;
        uint64_t newOrderId;
        uint32_t newSize;
        uint32_t newPrice;

        case 'S':
            readBytesIntoMessage(11);
            break;
        case 'R':
            readBytesIntoMessage(38);
            break;
        case 'H':
            readBytesIntoMessage(24);
            break;
        case 'Y':
            readBytesIntoMessage(19);
            break;
        case 'L':
            readBytesIntoMessage(25);
            break;
        case 'V':
            readBytesIntoMessage(34);
            break;
        case 'W':
            readBytesIntoMessage(11);
            break;
        case 'K':
            readBytesIntoMessage(27);
            break;
        case 'J':
            readBytesIntoMessage(34);
            break;
        case 'h':
            readBytesIntoMessage(20);
            break;
        case 'A':
            readBytesIntoMessage(35);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            if(strcmp(ticker,stock.c_str())){
                return msg;
            }
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            price = parse_uint32(message+31);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setRemSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'F':
            readBytesIntoMessage(39);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            if(strcmp(ticker,stock.c_str())){
                return msg;
            }
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            price = parse_uint32(message+31);
            // char mpid[5]; strncpy(mpid, message+35, 4); mpid[4] = 0;
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setRemSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'E':
            readBytesIntoMessage(30);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            execSize = parse_uint32(message+18);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setExecSize(static_cast<size_type>(execSize));
            break;
        case 'C':
            readBytesIntoMessage(35);
            // uint16_t locateCode = parse_uint16(message);
            // uint16_t trackingNumb = parse_uint16(message+2);
            // uint64_t timeStamp = parse_ts(message+4);
            // uint64_t orderId = parse_uint64(message+10);
            // uint32_t execSize = parse_uint32(message+18);
            // // uint64_t matchNumber = parse_uint64(message+22);
            // char printable = message[30];
            // uint32_t price = parse_uint32(message+31);

            // Check how to use C.
            break;
        case 'X':
            readBytesIntoMessage(22);
            // uint16_t locateCode = parse_uint16(message);
            // uint16_t trackingNumb = parse_uint16(message+2);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            cancSize = parse_uint32(message+18);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setCancSize(static_cast<size_type>(cancSize));
            break;
        case 'D':
            readBytesIntoMessage(18);
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            break;
        case 'U':
            readBytesIntoMessage(34);
            timeStamp = parse_ts(message+4);
            oldOrderId = parse_uint64(message+10);
            newOrderId = parse_uint64(message+18);
            newSize = parse_uint32(message+26);
            newPrice = parse_uint32(message+30);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(newOrderId));
            msg.setOldId(static_cast<id_type>(oldOrderId));
            msg.setRemSize(static_cast<size_type>(newSize));
            msg.setPrice(static_cast<price_type>(newPrice)/10000);
            break;
        case 'P':
            readBytesIntoMessage(43);
            strncpy(ticker, message+23, 8); ticker[8] = 0;
            if(strcmp(ticker,stock.c_str())){
                return msg;
            }
            timeStamp = parse_ts(message+4);
            orderId = parse_uint64(message+10);
            direction = message[18];
            size = parse_uint32(message+19);
            price = parse_uint32(message+31);
            msg.setType(std::string(1,key));
            msg.setTimeStamp(static_cast<time_type>(timeStamp));
            msg.setId(static_cast<id_type>(orderId));
            msg.setSide(static_cast<side_type>(direction == 'S'));
            msg.setExecSize(static_cast<size_type>(size));
            msg.setPrice(static_cast<price_type>(price)/10000);
            break;
        case 'Q':
            readBytesIntoMessage(39);
            // // uint16_t locateCode = parse_uint16(message);
            // // uint16_t trackingNumb = parse_uint16(message+2);
            // uint64_t timeStamp = parse_ts(message+4);
            // uint64_t size = parse_uint64(message+10);
            // char stock[9]; strncpy(stock, message+18, 8); stock[8] = 0;
            // uint32_t price = parse_uint32(message+26);
            // // uint64_t matchId = parse_uint64(message+30);
            // char crossType = message[38];

            // Check how to use Q.
            break;
        case 'B':
            readBytesIntoMessage(18);
            break;
        case 'I':
            readBytesIntoMessage(49);
            break;
        default:
            if(!eof()){
                std::cerr << "Type " << key <<" not found @ line: " << std::endl;
            }
            break;
    }
    return msg;
}

bool Reader::eof(){
    return file.eof();
}

bool Reader::isGood() const{
    return goodFile;
}

std::string Reader::getFileName(void) const{
    return fileName;
}

std::string Reader::getStock(void) const{
    return stock;
}

void Reader::setMessage(const char* str){
    memcpy(message, str, 64);
}

Reader::~Reader(){
    if (file.is_open()){
        file.close();
        std::cout<<"file "<<fileName<<" has been closed"<<std::endl;
        std::cout << "Finished, processed " << count << " messages in " << difftime(time(0),start) << "seconds."  << std::endl;
    }
}
