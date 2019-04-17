#include <ITCH/OrderBook.hpp>

std::string OrderBook::getString(const size_t &level) const {
    size_t buyDepth = buySide.size();
    size_t sellDepth = sellSide.size();
    std::ostringstream string_builder;
    string_builder << timestamp << ",";

    std::map<price_type,size_type>::const_reverse_iterator it_buy = buySide.rbegin();
    std::map<price_type,size_type>::const_iterator it_sell = sellSide.begin();


    for (unsigned i = 0; i < level; i++) {
        //result:  "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..."

        if( i < buyDepth){
            string_builder << it_buy->first << ","<< it_buy->second << ",";
            ++it_buy;
        }
        else // no more prices in buy side
             string_builder << ",,";

        if (i < sellDepth){
            string_builder << it_sell->first << "," << it_sell->second << ",";
            ++it_sell;
        }
        else // no more prices in sell side
            string_builder << ",,";
    }

    //remove last 1 characters from string stream: comma
    string_builder.seekp(-1, std::ios_base::end);
    string_builder << std::endl;
    return string_builder.str();

 }

void OrderBook::modifySize(price_type price, size_type size, side_type side){
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

void OrderBook::setTimeStamp(const time_type &t){
    timestamp = t;
}
