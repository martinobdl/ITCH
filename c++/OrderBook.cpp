#include "OrderBook.hpp"

std::string OrderBook::getString(unsigned level) const {
    unsigned buyDepth = buySide.size();
    unsigned sellDepth = sellSide.size();
    std::ostringstream string_builder;
    string_builder << timestamp << ",";

    std::map<double,long>::const_reverse_iterator it_buy = buySide.rbegin();
    std::map<double,long>::const_iterator it_sell = sellSide.begin();


    for (unsigned i = 0; i < level; i++) {
        //result:  "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..."
        
        if( i < buyDepth){
            string_builder << it_buy->first << ","<< it_buy->second << ",";
            ++it_buy;
        }
        else // no more prices in buy side
             string_builder << "0,0,";

        if (i < sellDepth){
            string_builder << it_sell->first << "," << it_sell->second << ",";
            ++it_sell;
        }
        else // no more prices in sell side
            string_builder << "0,0,";
    }

    //remove last 1 characters from string stream: comma
    string_builder.seekp(-1, std::ios_base::end);
    string_builder << std::endl;
    return string_builder.str();

 } 



void OrderBook::modifySize(double price, long size, bool side){
    if (side){ // modify sellSide
        sellSide[price] += size;
        if (sellSide[price] == 0 )
            sellSide.erase(price);
        else if(sellSide[price] < 0)
            std::cerr << "Negative size in order book is found! " << std::endl;
    }
    else {// modify buySide
        buySide[price] += size;
        if (buySide[price] == 0 )
            buySide.erase(price);
        else if(buySide[price] < 0)
            std::cerr << "Negative size in order book is found! " << std::endl;
    }
}

void OrderBook::setTimeStamp(const long &t){
    timestamp = t;
}
