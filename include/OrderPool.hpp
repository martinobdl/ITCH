#ifndef _ORDERPOOL_H_
#define _ORDERPOOL_H_

#include <unordered_map>
#include <Order.hpp>
#include <utility.hpp>

class OrderPool{

    std::unordered_map<id_type,Order> pool;

    public:
    OrderPool() = default;
    Order searchOrderPool(id_type);
    void addToOrderPool(id_type, bool, size_type, price_type);
    void modifyOrder(id_type, size_type);
    bool isEmpty(void) const;
    void printIds(void) const;
};

#endif /*_ORDERPOOL_H_*/
