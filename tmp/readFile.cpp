#include <iostream>
#include <fstream>

/*
* This takes: 100s
* for 360Mio ~ 4'764'426'114 bytes
* 3.6 Mio Messages/sec.
*/

int main(){
    std::ifstream myfile;
    char c;
    char buffer[30];
    myfile.open("../data/binary/01302019.NASDAQ_ITCH50.gz");
    while (!myfile.eof()){
        myfile.read(buffer,1);
    }
    myfile.close();
    return 0;
}
