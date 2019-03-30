#ifndef _Order_H_
#define _Order_H_

#include <iostream>
#include "utility.hpp"
#include "Message.hpp"

// type def for attributes ?
class Order{
    id_type id=0;
    bool side; // 0 for buy, 1 for sell
    size_type size=0; // the LOBSTER report puts here size and remaning size. Dunno why.
    price_type price=0;

    public:
    Order()=default;
    Order(id_type _id, bool _side, size_type _size, price_type _price);
    void addSize(size_type size); // also negative

    //setters
    void setId(id_type _id);
    void setSide(bool _side);
    void setSize(size_type size);
    void setPrice(price_type _price);

    //getters
    id_type getId(void) const;
    bool getSide(void) const;
    size_type getSize(void) const;
    price_type getPrice(void) const;

    //print
    void print() const;
    bool isEmpty(void) const;
};



#endif /*_Order_H_*/
