#include <OrderBook.hpp>

/**
 * Make comma-separated string from information available
 * in the OrderBook about the best bid/ask prices and corresponding sizes up to number of levels :
 * "1.BidPrice, 1.BidSize,1.AskPrice,1.AskSize,..,level.BidPrice, level.BidSize,level.AskPrice,level.AskSize"
 *
 * @param[in] level up to what level to write the price/size tuple.
 *
 */
std::string OrderBook::getString(const size_t &level) const {

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
        else{ // no prices on buy side left
            string_builder << ",,";
        }

        if (i < sellDepth){
            string_builder << it_sell->first << "," << it_sell->second << ",";
            ++it_sell;
        }
        else{ // no prices on sell side left
            string_builder << ",,";
        }
    }

    // Removing the last character from string stream: comma
    string_builder.seekp(-1, std::ios_base::end);
    string_builder << std::endl;

    return string_builder.str();

 }

/**
 * Performs actions on the double map reoresenting the OrderBook
 *
 * @param[in] price modify map corresponding to price
 * @param[in] size add (or delete if size is negatinve) the size corrsponding to price
 * @param[in] side 0 for buy side and 1 for sell side.
 *
 */
void OrderBook::modifySize(price_type price, size_type size, side_type side){
    if (side){ // modify sellSide
        sellSide[price] += size;
        if (sellSide[price] == 0 )
            sellSide.erase(price);
        else if(sellSide[price] < 0)
            std::cerr << "Negative size in order book is found! " << std::endl;
    }
    else{ // modify buySide
        buySide[price] += size;
        if (buySide[price] == 0 )
            buySide.erase(price);
        else if(buySide[price] < 0)
            std::cerr << "Negative size in order book is found! " << std::endl;
    }
}

/**
 * Check if the biggest bid price is less than smallest ask
 *
 * @return bool value of the check. 1 OK, 0 KO.
 */
bool OrderBook::checkBookConsistency(){
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
