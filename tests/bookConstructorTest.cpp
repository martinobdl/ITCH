#include "../c++/BookConstructor.hpp"

int main(){
    std::string nameFile = "/Users/Martino/Documents/ITCH/20180830.PSX_ITCH_50_parsed.csv";
    std::string stock = "AAPL";
    std::string stockPadded = stock;
    stockPadded.insert(stockPadded.end(), 8 - stockPadded.size(), ' ');
    BookConstructor B(nameFile, nameFile+"_"+stock+"_out_message", nameFile+"_"+stock+"_out_book", "LFC     ");
    B.start();
}
