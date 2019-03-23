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

void Message::setRemSize(const size_type& _size){
remSize=_size;
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
std::cout<<"Message type   :" << type <<std::endl;
std::cout<<"Id             :"<<id<< std::endl;
std::cout<<"timestamp      :" << timestamp <<std::endl;
std::cout<<"side           :" << side <<std::endl;
std::cout<<"price          :"<<price<<std::endl;
std::cout<<"remaining size :" << remSize <<std::endl;
if (type == "D") std::cout<<"deletion size  :" << cancSize <<std::endl;
if (type == "E") std::cout<<"execution size :" << execSize <<std::endl;
if (type =="U"){
  std::cout<< "old Id         :" << oldId <<std::endl;
  std::cout<< "old size       :"<< oldSize <<std::endl;
  std::cout<< "old price      :" << oldPrice <<std::endl;
};
std::cout<< "" <<std::endl;
};
