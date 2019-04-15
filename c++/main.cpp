#include <iostream>
#include <string>
#include "../c++/BookConstructor.hpp"

int main(int argc, char * argv[]){
    size_t levels;
    bool debug = 0;
    if(argc < 3){
        std::cerr << "Call it with: path to ITCH Parsed, Stock name, [optional] number of levels, [optional] -D" << std::endl;
        return 0;
    }
    else if(argc == 3){
        levels = 1;
        debug = 0;
    }
    else if(argc == 4){
        levels = std::stoul(argv[3]);
    }
    else if(argc == 5){
        levels = std::stoul(argv[3]);
        debug = (std::string(argv[4])=="-D");
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
        levels,
        debug);

    BookConstructor.start();
}
