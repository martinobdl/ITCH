#ifndef _OrderPool_H_
#define _OrderPool_H_

#include <unordered_map>
#include "Order.hpp"
#include "utility.hpp"

class OrderPool{

    std::unordered_map<id_type,Order> pool;

    //bool inPool(id_type id);

    public:
    OrderPool() = default;
    Order findOrderPool(id_type id);
    void addToOrderPool(id_type id, bool side, size_type size, price_type price);
    void modifyOrder(id_type idOrder, size_type size);

};



#endif /*_OrderPool_H_*/
