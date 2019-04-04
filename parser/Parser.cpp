#include "Parser.hpp"

Parser::Parser(const std::string &inFileName, const std::string &outFileName){
    inFile.open(inFileName);
    if(!inFile.is_open()){
        std::cerr << "Can't open input file " << inFileName << std::endl;
    }
    else
        std::cout << "Opened "+inFileName+" to parse." << std::endl;
    outFile.open(outFileName);
    count = 0;
    start = time(0);
}

void Parser::writeChunk(const char *type){
    //
    // given a char array type like Ix
    // interprets and write the following x bytes as indicated by the first keycode
    // Ix: interprets and write the following x bytes as integers in big-endian order
    // Ax: interprets and write the following x bytes as alphabetic
    // Px,n interprets and write the following x bytes as a float number with n decimal digits
    // *.: writes also a \r\n
    // X: writes the single letter X to the output file. Should be the message indicator.
    //
    if(strlen(type)==1){
        outFile << type << "," ;
        return;
    }
    std::size_t len = strlen(type);
    const size_t size = (len>1) ? std::stoul(&type[1]) : 1;
    const long size_l = (len>1) ? std::stol(&type[1]) : 1;
    const std::string sep = (len>2 and type[len-1]=='.') ? "\r\n" : ",";
    std::vector<unsigned char> buffer(size);
    inFile.read(reinterpret_cast<char *>(&buffer[0]), size_l);
    if(type[0]=='A'){
        copy(buffer.cbegin(), buffer.cend(), std::ostreambuf_iterator<char>(outFile));
    }
    else if(type[0]=='I' or type[0]=='P'){
        long num = 0;
        for(size_t i = 0; i < size; i++){
            num *= (1<<8);
            num += buffer[i];
        }
        if(type[0]=='P' and len>3){
            int N = atoi(&(type[3]));
            outFile << num/pow(10,N) ;
        }
        else outFile << num;
    }
    outFile << sep;
}

void Parser::writeMessage(const std::string &format){
    //
    // splits the format string and calls wrtieChunk with the specified interpretation.
    //
    char key = format[0];
    auto it = format_map.find(key);
    std::vector<std::string> types;
    if(it == format_map.end()){
        types = split(format,"-");
        format_map.insert(std::make_pair(key,types));
    }
    else
        types = it->second;
    for(std::string t: types){
        writeChunk(t.c_str());
    }
    count ++;
    if((count % 5000000)==0){
        std::cout << "Processed " << count/1000000 << "Mio messages. " << count/difftime(time(0), start) << " messages per sec." << std::endl;
    }
}

void Parser::closeStreams(){
    inFile.close();
    outFile.close();
    std::cout << "Finished, processed " << count << " messages in " << difftime(time(0),start) << "seconds."  << std::endl;
}

void Parser::process(){
    char c;
    while(inFile.get(c)){
        //
        // First letter is the type of message.
        // -: separator
        // Ix: x bytes Integer
        // Ax: x bytes Alpha
        // Px,n: x bytes, n decimal precision
        // .: end of message. Write "\r\n"
        //
        if('S'==c) writeMessage("S-I2-I2-I6-A1.");
        if('R'==c) writeMessage("R-I2-I2-I6-A8-A1-A1-I4-A1-A1-A2-A1-A1-A1-A1-A1-I4-A1.");
        if('H'==c) writeMessage("H-I2-I2-I6-A8-A1-A1-A4.");
        if('Y'==c) writeMessage("Y-I2-I2-I6-A8-A1.");
        if('L'==c) writeMessage("L-I2-I2-I6-A4-A8-A1-A1-A1.");
        if('V'==c) writeMessage("V-I2-I2-I6-P8,8-P8,8-P8,8.");
        if('W'==c) writeMessage("W-I2-I2-I6-A1.");
        if('K'==c) writeMessage("K-I2-I2-I6-A8-I4-A1-P4,4.");
        if('J'==c) writeMessage("J-I2-I2-I6-A8-P4,4-P4,4-P4,4-I4.");
        if('h'==c) writeMessage("h-I2-I2-I6-A8-A1-A1.");
        if('A'==c) writeMessage("A-I2-I2-I6-I8-A1-I4-A8-P4,4.");
        if('F'==c) writeMessage("F-I2-I2-I6-I8-A1-I4-A8-P4,4-A4.");
        if('E'==c) writeMessage("E-I2-I2-I6-I8-I4-I8.");
        if('C'==c) writeMessage("C-I2-I2-I6-I8-I4-I8-A1-P4,4.");
        if('X'==c) writeMessage("X-I2-I2-I6-I8-I4.");
        if('D'==c) writeMessage("D-I2-I2-I6-I8.");
        if('U'==c) writeMessage("U-I2-I2-I6-I8-I8-I4-P4,4.");
        if('P'==c) writeMessage("P-I2-I2-I6-I8-A1-I4-A8-P4,4-I8.");
        if('Q'==c) writeMessage("Q-I2-I2-I6-I8-A8-P4,4-I8-A1.");
        if('B'==c) writeMessage("B-I2-I2-I6-I8.");
        if('I'==c) writeMessage("I-I2-I2-I6-I8-I8-A1-A8-P4,4-P4,4-P4,4-A1,A1.");
    }
    closeStreams();
}
