#include <iostream>
#include "Message.hpp"

Message::Message(const std::string& _type, const id_type& _id, const long& _timestamp):type(_type), id(_id),timestamp(_timestamp){};

void Message::setType(const std::string& _type){
type=_type;
};

void Message::setId(const id_type& _id){
id=_id;
};

void Message::setTimestamp(const long& _timestamp){
timestamp=_timestamp;
};

void Message::setSide(const bool& _side){
side=_side;
};

void Message::setPrice(const price_type& _price){
price=_price;
};

void Message::setCancSize(const size_type& _size){
cancSize=_size;
};

void Message::setExecSize(const size_type& _size){
execSize=_size;
};

void Message::setOldId(const id_type& _id){
oldId=_id;
};

void Message::setOldPrice(const price_type& _price){
oldPrice=_price;
};

void Message::setOldSize(const size_type& _size){
oldSize=_size;
};

void Message::print(){
std::cout<< "The message type is " << type <<",the ID is "<<id<<", the timestamp is " << timestamp <<std::endl;
std::cout<< "The old Id is " << oldId <<",the old size is "<<oldSize<<", the old price " << oldPrice <<std::endl;

};
