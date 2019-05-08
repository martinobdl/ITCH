#ifndef _ORDER_H_
#define _ORDER_H_

#include <iostream>
#include <utility.hpp>
#include <Message.hpp>

// The class keeps track of the order with specific id throughout a day.
// A sequence of messages with same ID are related to the same Order object.

class Order{
    id_type id = ID_DEFAULT;
    side_type side; // 0 for buy, 1 for sell
    size_type size = SIZE_DEFAULT;
    price_type price = PRICE_DEFAULT;

    public:
    Order() = default;
    Order(id_type _id, side_type _side, size_type _size, price_type _price);
    void addSize(size_type size);

    // setters
    // void setId(id_type _id);
    // void setSide(side_type _side);
    // void setSize(size_type size);
    // void setPrice(price_type _price);

    // getters
    id_type getId(void) const;
    side_type getSide(void) const;
    size_type getSize(void) const;
    price_type getPrice(void) const;

    void print(void) const;
    bool isEmpty(void) const;
};

#endif /*_ORDER_H_*/
