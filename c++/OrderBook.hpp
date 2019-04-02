#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "utility.hpp"

class OrderBook{
    time_type timestamp;
    std::map<price_type,size_type> buySide;
    std::map<price_type,size_type> sellSide;

    public:
    OrderBook(void) = default;
    // since this should be done at every time,
    // the datastructure of buySide/sellSide sould
    // be done accordingly (not sure map is the right one).
    std::string getString(const size_t &level) const; // "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..."
    void modifySize(price_type price, size_type size, bool side); // size also negative
    void setTimeStamp(const time_type &t);
};


#endif /*_OrderBook_H_*/
