#include "Order.hpp"


Order::Order(const Message& msg): id(msg.getID()), side(msg.getSide()), size(msg.getSize()), price(msg.getPrice()){} // ??? is it better to pass message object or variable by variable
Order::Order(long _id, bool _side, long _size, long _price): id(_id), side(_side), size(_size), price(_price) {}


//getters
long Order::getId() const{
    return id;
}
bool Order::getSide() const{
    return side;
}

long Order::getSize() const{
    return size;
}

long Order::getPrice() const{
    return price;
}


Order::addSize(long size){

}// also negative