#include "Parser.hpp"
#include <iostream>

int main(int argc, char * argv[]){
    if(argc < 2){
        std::cerr << "Call it with name of complete path of the ITCH_50 file as arg" << std::endl;
        return 0;
    }
    std::string pathFile = argv[1];
    std::string outFileName = pathFile+"_parsed.csv";
    Parser parser(argv[1],outFileName);
    parser.process();
    return 0;
}
