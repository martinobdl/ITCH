#include "../c++/BookConstructor.hpp"

int main(){
    std::string nameFile = "/Users/Martino/Documents/ITCH/20180830.PSX_ITCH_50_parsed.csv";
    std::string stock = "AAPL";

//    std::string nameFile = "/Users/Martino/Documents/GitHub/ITCH/tests/messagesTest.csv";
//    std::string stock = "LFC";

    std::string stockPadded = stock;
    int levels = 1;
    stockPadded.insert(stockPadded.end(), 8 - stockPadded.size(), ' ');
    BookConstructor B(nameFile,
        nameFile+"_"+stock+"_out_message.csv",
        nameFile+"_"+stock+"_out_book.csv",
        stockPadded,
        levels);
    B.start();
}
