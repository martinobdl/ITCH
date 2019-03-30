#include "Order.hpp"

Order::Order(id_type _id, bool _side, size_type _size, price_type _price): id(_id), side(_side), size(_size), price(_price) {}

//setters
void Order::setId(id_type _id){
    id=_id;
};

void Order::setSide(bool _side){
    side=_side;
};

void Order::setSize(size_type _size){
    size=_size;
};

void Order::setPrice(price_type _price){
    price=_price;
};


//getters
id_type Order::getId(void) const{
    return id;
};

bool Order::getSide(void) const{
    return side;
};

size_type Order::getSize(void) const{
    return size;
};

price_type Order::getPrice(void) const{
    return price;
};


void Order::addSize(size_type _size){
  size+=_size;
  if (size<0) std::cerr<<"Updated order has negative size"<<std::endl;
};// also negative

void Order::print() const{
  if (id!=0){
  std::cout<<"Id             :"<<id<< std::endl;
  std::cout<<"side           :" << side <<std::endl;
  std::cout<<"size           :" << size <<std::endl;
  std::cout<<"price          :"<<price<<std::endl;
  }else {
  std::cerr<<"Trying to print an empty order"<<std::endl;
}
};
