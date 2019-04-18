#ifndef _ORDERPOOL_H_
#define _ORDERPOOL_H_

#include <unordered_map>
#include <Order.hpp>
#include <utility.hpp>

class OrderPool{

    std::unordered_map<id_type,Order> pool;

    public:
    OrderPool() = default;
    Order findOrderPool(id_type id);
    void addToOrderPool(id_type id, bool side, size_type size, price_type price);
    void modifyOrder(id_type idOrder, size_type size);
    bool isEmpty(void) const;
    void printIds(void) const;
};

#endif /*_ORDERPOOL_H_*/
