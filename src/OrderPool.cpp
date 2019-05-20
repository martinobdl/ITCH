#include <OrderPool.hpp>

/**
 * Look for the Order specified by the id in the OrderPool
 *
 * @param[in] idOrder : id relative to the order quaried
 * @return Order with id equals to idOrder.
 *
 */
Order OrderPool::searchOrderPool(id_type idOrder){
    auto foundElement = pool.find(idOrder);
    Order foundOrder;
    if (foundElement != pool.end()){
        foundOrder = foundElement->second;
    }
    return foundOrder;
}

/**
 * Initialize and add an Order to the OrderPool
 *
 * @param[in] idOrder id of the order to add
 * @param[in] side side of the order to add (0 for buy and 1 for sell)
 * @param[in] size size of the order to add to the pool
 * @param[in] price limit price of the order to add
 *
 */
void OrderPool::addToOrderPool(id_type idOrder, bool side, size_type size, price_type price){
    Order orderToAdd(idOrder, side, size, price);
    pool[idOrder] = orderToAdd;
}

/**
 * Delete size of an order in the OrderPool.
 *
 * If the remaining size if zero then order get deleted from the OrderPool.
 * size is always subtracted from the order.
 *
 * @param[in] idOrder id of the order to modify
 * @param[in] size size to subtract from the order.
 *
 */
void OrderPool::modifyOrder(id_type idOrder, size_type size = 0){
    pool[idOrder].addSize(-size);
    if( pool[idOrder].getSize() == 0 ){
        pool.erase(idOrder);
    }
}

/**
 * Check wether the OrderPool map is empty
 *
 * @return book, 1 if empty, 0 if not.
 */
bool OrderPool::isEmpty(void) const{
    return pool.empty();
}

/**
 * Prints id of all orders in the OrderPool.
 *
 * It's used at the end to check if the OrderPool is empty (should be).
 *
 */
void OrderPool::printIds(void) const{
    for(auto items: pool){
        std::cout << items.first << std::endl;
    }
};
