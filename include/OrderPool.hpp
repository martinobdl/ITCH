#ifndef _ORDERPOOL_H_
#define _ORDERPOOL_H_

#include <unordered_map>
#include <Order.hpp>
#include <utility.hpp>

// The class tracks all Order objects created.
// When an “A” (or “F”) message comes in, it creates a Order object in the OrderPool.
// When subsequently a message comes in indicating limit order cancellation (“X” and “D”) 
// or a limit order execution (“E”), the information about the price and size of the original 
// limit order is retrieved from the OrderPool using common order ID.

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
