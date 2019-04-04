#include <iostream>
#include <string>
#include "../c++/BookConstructor.hpp"

int main(int argc, char * argv[]){
    size_t levels;
    if(argc < 3){
        std::cerr << "Call it with: path to ITCH Parsed, Stock name, [optional] number of levels" << std::endl;
        return 0;
    }
    else if(argc == 3){
        levels = 1;
    }
    else{
        levels = std::stoul(argv[3]);
    }
    std::string pathFile = argv[1];
    std::string stock = argv[2];
    std::string outBookFileName = pathFile+"_"+stock+"_out_book.csv";
    std::string outMessageFileName = pathFile+"_"+stock+"_out_message.csv";
    std::string stockPadded = stock;
    stockPadded.insert(stockPadded.end(), 8 - stockPadded.size(), ' ');

    BookConstructor BookConstructor(pathFile,
        outMessageFileName,
        outBookFileName,
        stockPadded,
        levels);

    BookConstructor.start();
}
