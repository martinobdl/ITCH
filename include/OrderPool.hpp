#ifndef _ORDERPOOL_H_
#define _ORDERPOOL_H_

#include <unordered_map>
#include <Order.hpp>
#include <utility.hpp>

/**
 * The class tracks all Order objects created.
 * When an “A” (or “F”) message comes in, it creates a Order object in the OrderPool.
 * When subsequently a message comes in indicating limit order cancellation (“X” and “D”)
 * or a limit order execution (“E”), the information about the price and size of the original
 * limit order is retrieved from the OrderPool using common order ID.
 *
 */

class OrderPool{

    std::unordered_map<id_type,Order> pool;

    public:
    OrderPool() = default;

    /**
     * Look for the Order specified by the id in the OrderPool
     *
     * @param[in] idOrder : id relative to the order quaried
     * @return Order with id equals to idOrder.
     *
     */
    Order searchOrderPool(id_type);

    /**
     * Initialize and add an Order to the OrderPool
     *
     * @param[in] idOrder id of the order to add
     * @param[in] side side of the order to add (0 for buy and 1 for sell)
     * @param[in] size size of the order to add to the pool
     * @param[in] price limit price of the order to add
     *
     */
    void addToOrderPool(id_type, bool, size_type, price_type);

    /**
     * Delete size of an order in the OrderPool.
     *
     * If the remaining size is zero then order is deleted from the OrderPool.
     * size is always subtracted from the order.
     *
     * @param[in] idOrder id of the order to modify
     * @param[in] size size to subtract from the order.
     *
     */
    void modifyOrder(id_type, size_type);

    /**
     * Check whether the OrderPool map is empty
     *
     * @return book, 1 if empty, 0 if not.
     */
    bool isEmpty(void) const;

    /**
     * Prints id of all orders in the OrderPool.
     *
     * It's used at the end to check if the OrderPool is empty (it should be).
     *
     */
    void printIds(void) const;
};

#endif /*_ORDERPOOL_H_*/
