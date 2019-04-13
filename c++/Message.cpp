#include "Message.hpp"

Message::Message(const std::string& _type,
    const id_type& _id,
    const time_type& _timestamp):
        type(_type),
        id(_id),
        timestamp(_timestamp){};

void Message::setType(const std::string& _type){
    if(_type =="A" || _type == "F"){
        type = "A"; // add
    }
    else if (_type == "D" || _type == "X"){
        type = "D"; // delete
    }
    else if (_type == "U"){
        type = "R"; // replace
    }
    else if (_type == "E"){
        type = _type; // execute
    }
    else if (_type == "P"){
        type = _type; // execute hidden
    }
    else{
        std::cerr << "Message with wrong type (" << _type << ") has been found!"<< std::endl;
    }
}

void Message::setId(const id_type& _id){
    id=_id;
}

void Message::setTimeStamp(const time_type& _timestamp){
    timestamp=_timestamp;
}

void Message::setSide(const side_type& _side){
    side=_side;
}

void Message::setPrice(const price_type& _price){
    price=_price;
}

void Message::setRemSize(const size_type& _size){
    remSize=_size;
}

void Message::setCancSize(const size_type& _size){
    cancSize=_size;
}

void Message::setExecSize(const size_type& _size){
    execSize=_size;
}

void Message::setOldId(const id_type& _id){
    oldId=_id;
}

void Message::setOldPrice(const price_type& _price){
    oldPrice=_price;
}

void Message::setOldSize(const size_type& _size){
    oldSize=_size;
}

// getters
std::string Message::getType() const{
    return type;
}

id_type Message::getId() const{
    return id;
}

time_type Message::getTimeStamp()const{
    return timestamp;
}

side_type Message::getSide()const{
    return side;
}

price_type Message::getPrice()const{
    return price;
}

size_type Message::getRemSize()const{
    return remSize;
}

size_type Message::getCancSize()const{
    return cancSize;
}

size_type Message::getExecSize()const{
    return execSize;
}

id_type Message::getOldId()const{
    return oldId;
}

price_type Message::getOldPrice()const{
    return oldPrice;
}

size_type Message::getOldSize()const{
    return oldSize;
}

bool Message::isEmpty()const{
    return (id==ID_DEFAULT);
}

std::string Message::getString()const{
    std::ostringstream string_builder;
    string_builder  << type << ",";

    if(!isEmpty()){
        string_builder  << timestamp  << ","
                        << id << ","
                        << side << ",";
    }
    else{
        string_builder  << ","
                        << ","
                        << ",";
    }
    if(remSize!=SIZE_DEFAULT){
        string_builder << remSize;
    }
    string_builder << ",";

    if(price!=PRICE_DEFAULT){
        string_builder << price;
    }
    string_builder << ",";

    if(cancSize!=SIZE_DEFAULT){
        string_builder << cancSize;
    }
    string_builder << ",";

    if(execSize!=SIZE_DEFAULT){
        string_builder << execSize;
    }
    string_builder << ",";

    if(oldId!=ID_DEFAULT){
        string_builder << oldId;
    }
    string_builder << ",";

    if(oldSize!=SIZE_DEFAULT){
        string_builder << oldSize;
    }
    string_builder << ",";

    if(oldPrice!=PRICE_DEFAULT){
        string_builder << oldPrice;
    }
    string_builder << std::endl;

    return string_builder.str();
}

void Message::print() const {
    std::cout<<"Message type   :" << type <<std::endl;
    std::cout<<"Id             :"<<id<< std::endl;
    std::cout<<"timestamp      :" << timestamp <<std::endl;
    std::cout<<"side           :" << side <<std::endl;
    std::cout<<"price          :"<<price<<std::endl;
    std::cout<<"remaining size :" << remSize <<std::endl;
    if (type == "D"){
        std::cout<<"deletion size  :" << cancSize <<std::endl;
    }
    if (type == "E"){
        std::cout<<"execution size :" << execSize <<std::endl;
    }
    if (type =="U"){
        std::cout<< "old Id         :" << oldId <<std::endl;
        std::cout<< "old size       :"<< oldSize <<std::endl;
        std::cout<< "old price      :" << oldPrice <<std::endl;
    }
    std::cout<< "" <<std::endl;
}
