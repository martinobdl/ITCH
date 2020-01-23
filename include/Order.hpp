#ifndef _ORDER_H_
#define _ORDER_H_

#include <iostream>
#include <utility.hpp>
#include <Message.hpp>

class Order{
    id_type id = ID_DEFAULT;
    side_type side;
    size_type size = SIZE_DEFAULT;
    price_type price = PRICE_DEFAULT;
    char mpid[5] = "";

    public:
    Order() = default;
    Order(id_type _id, side_type _side, size_type _size, price_type _price, const char *_mpid);

    /**
    * Add or subtract size to the order.
    *
    * @param[in] _size : size to add or detract (if size is negative) to the order
    */
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
    const char * getMPID(void) const;

    void print(void) const;

    /**
    * Check whether the Order is unsetted or not.
    *
    * @return bool, 1 is unsetted (Empty), 0 if setted.
    */
    bool isEmpty(void) const;
};

#endif /*_ORDER_H_*/
