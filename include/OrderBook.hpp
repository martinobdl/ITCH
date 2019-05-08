#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <utility.hpp>

// Class containing list of buy and sell orders for a specific security
// organized by price level into 2 ordered maps. An order book lists the number of 
// shares being bid or offered at each price point available, keeping track of time
// of every change made. 

class OrderBook{
    time_type timestamp;
    std::map<price_type, size_type> buySide;
    std::map<price_type, size_type> sellSide;

    public:
    OrderBook(void) = default;

    std::string getString(const size_t &) const; 
    // Make comma-separated string from information available
    // in the book about the best bid/ask prices and corresponding sizes up to number of levels :
    // "1.BidPrice, 1.BidSize,1.AskPrice,1.AskSize,..,level.BidPrice, level.BidSize,level.AskPrice,level.AskSize"
    // If not given by the user, input argument takes default value = 5


    void modifySize(price_type, size_type, side_type);  
    void setTimeStamp(const time_type &);
    bool checkBookConsistency(void); // Bid prices have to be less than ask prices.
};


#endif /*_OrderBook_H_*/
