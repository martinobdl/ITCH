#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <utility.hpp>

/**
 * Class containing list of buy and sell orders for a specific security
 * organized by price level into 2 ordered maps. An order book lists the number of
 * shares being bid or offered at each price point available, keeping track of time
 * of every change made.
 *
 */

class OrderBook{
    time_type timestamp;
    std::map<price_type, size_type> buySide;
    std::map<price_type, size_type> sellSide;

    public:
    OrderBook(void) = default;

    /**
     * Make comma-separated string from information available
     * in the OrderBook about the best bid/ask prices and corresponding sizes up to number of levels :
     * "1.BidPrice, 1.BidSize,1.AskPrice,1.AskSize,..,level.BidPrice, level.BidSize,level.AskPrice,level.AskSize"
     *
     * @param[in] level up to what level to write the price/size tuple.
     *
     */
    std::string getString(const size_t &) const;

    /**
     * Performs actions on the double map representing the OrderBook
     *
     * @param[in] price modify map corresponding to price
     * @param[in] size add (or delete if size is negative) the size corresponding to price
     * @param[in] side 0 for buy side and 1 for sell side.
     *
     */
    void modifySize(price_type, size_type, side_type);
    void setTimeStamp(const time_type &);

    /**
     * Check if the biggest bid price is less than smallest ask
     *
     * @return bool value of the check. 1 OK, 0 KO.
     */
    bool checkBookConsistency(void);
};


#endif /*_OrderBook_H_*/
