#include "../c++/OrderBook.hpp"
#include <iostream>

int main(){
    OrderBook OB;
    OB.setTimeStamp(1);
    OB.modifySize(12,7,0);
    OB.modifySize(3,4,0);
    OB.modifySize(15,12,1);
    OB.modifySize(25,11,1);
    OB.modifySize(33,34,1);
    std::cout << OB.getStringRepresentation(5) << std::endl;
    return 0;
}
