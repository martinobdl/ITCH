#include <iostream>
#include <string>
#include <BookConstructor.hpp>

int main(int argc, char * argv[]){

    if(argc<5){
        std::cerr << "The program should be called with: ./BookConstructor path_input_file dir_book dir_messages levels stock" << std::endl;
        return 0;
    }

    std::string pathFile = argv[1];
    std::string outBookDirectory = argv[2];
    std::string outMessageDirectory = argv[3];
    size_t levels = std::stoul(argv[4]);
    std::string stock = argv[5];
    std::string nameFile = getFileName(pathFile);
    std::string outBookFileName = outBookDirectory+nameFile+"_"+stock+"_book_"+std::to_string(levels)+".csv";
    std::string outMessageFileName = outMessageDirectory+nameFile+"_"+stock+"_message.csv";
    std::string stockPadded = stock;
    stockPadded.insert(stockPadded.end(), 8 - stockPadded.size(), ' ');

    BookConstructor BookConstructor(pathFile,
        outMessageFileName,
        outBookFileName,
        stockPadded,
        levels);

    BookConstructor.start();

    return 1;
}
