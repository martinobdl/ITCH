#include <OrderBook.hpp>

std::string OrderBook::getString(const size_t &level) const {
    // Make comma-separated string from information available
    // in the book about the best bid/ask prices and corresponding sizes up to number of levels :
    // "1.BidPrice, 1.BidSize,1.AskPrice,1.AskSize,..,level.BidPrice, level.BidSize,level.AskPrice,level.AskSize"
    //  If not given by the user, input argument takes default value = 5


    size_t buyDepth = buySide.size(); // The number of bid prices available in the book
    size_t sellDepth = sellSide.size(); // The number of ask prices available in the book
    std::ostringstream string_builder;
    string_builder << timestamp << ",";

    // The best bid price is the smallest value stored in ordered map
    std::map<price_type,size_type>::const_reverse_iterator it_buy = buySide.rbegin();

    // The best ask price is the biggest value stored in ordered map
    std::map<price_type,size_type>::const_iterator it_sell = sellSide.begin();


    for (unsigned i = 0; i < level; i++){
        if( i < buyDepth){
            string_builder << it_buy->first << ","<< it_buy->second << ",";
            ++it_buy;
        }
        else // no prices on buy side left
             string_builder << ",,";

        if (i < sellDepth){
            string_builder << it_sell->first << "," << it_sell->second << ",";
            ++it_sell;
        }
        else // no prices on sell side left
            string_builder << ",,";
    }

    // Removing the last character from string stream: comma
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
    else { // modify buySide
        buySide[price] += size;
        if (buySide[price] == 0 )
            buySide.erase(price);
        else if(buySide[price] < 0)
            std::cerr << "Negative size in order book is found! " << std::endl;
    }
}

bool OrderBook::checkBookConsistency(){
    // Check if the biggest bid price is less than smallest ask
    if (!(buySide.empty() or sellSide.empty())){
        return ((buySide.rbegin()->first) <= (sellSide.begin()->first));
    }
    else{
        return 1;
    }
}

void OrderBook::setTimeStamp(const time_type &t){
    timestamp = t;
}
