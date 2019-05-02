#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <utility.hpp>

class OrderBook{
    time_type timestamp;
    std::map<price_type, size_type> buySide;
    std::map<price_type, size_type> sellSide;

    public:
    OrderBook(void) = default;

    std::string getString(const size_t &) const; // ??? "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..." 

    void modifySize(price_type, size_type, side_type);  
    void setTimeStamp(const time_type &);
    bool checkBookConsistency(void); // Bid prices have to be less than ask prices.
};


#endif /*_OrderBook_H_*/
