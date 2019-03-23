#include "../c++/Message.hpp"
#include "../c++/Reader.hpp"

int main(){
    Reader r("mexTest.csv","LFC     ");
    while(!r.eof()){
        Message msg = r.createMessage();
        msg.print(); 
    }
    return 0;
}
