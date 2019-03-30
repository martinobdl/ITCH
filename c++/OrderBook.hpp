#ifndef _OrderBook_H_
#define _OrderBook_H_

#include <map>
#include <string>
#include <sstream>
#include <iostream>

class OrderBook{
    long timestamp;
    std::map<long,long> buySide;
    std::map<long,long> sellSide;
    
    public:
    OrderBook(void) = default;
    // since this should be done at every time, 
    // the datastructure of buySide/sellSide sould 
    // be done accordingly (not sure map is the right one).
    std::string getString(unsigned) const; // "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..."
    void modifySize(long price, long size, bool side); // size also negative
    void setTimeStamp(const long &t);
};


#endif /*_OrderBook_H_*/
