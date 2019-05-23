#include "Order.hpp"

Order::Order(id_type _id,
            bool _side,
            size_type _size,
            price_type _price):
        id(_id),
        side(_side),
        size(_size),
        price(_price){}

id_type Order::getId(void) const{
    return id;
}

bool Order::getSide(void) const{
    return side;
}

size_type Order::getSize(void) const{
    return size;
}

price_type Order::getPrice(void) const{
    return price;
}

void Order::addSize(size_type _size){
    size+=_size;
    if(size<0){
        std::cerr << "Updated order has negative size" << std::endl;
        print();
    }
}

void Order::print() const{
    if (id != ID_DEFAULT){
        std::cout << "Id             :" <<id<< std::endl;
        std::cout << "side           :" << side <<std::endl;
        std::cout << "size           :" << size <<std::endl;
        std::cout << "price          :" <<price<<std::endl;
    }
    else{
        std::cerr << "Trying to print an empty order" << std::endl;
    }
}

bool Order::isEmpty() const{
    return (id == ID_DEFAULT);
}
