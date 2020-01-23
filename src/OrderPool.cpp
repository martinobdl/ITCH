#include <OrderPool.hpp>

Order OrderPool::searchOrderPool(id_type idOrder){
    auto foundElement = pool.find(idOrder);
    Order foundOrder;
    if (foundElement != pool.end()){
        foundOrder = foundElement->second;
    }
    return foundOrder;
}

void OrderPool::addToOrderPool(id_type idOrder, bool side, size_type size, price_type price, const char *mpid){
    Order orderToAdd(idOrder, side, size, price, mpid);
    pool[idOrder] = orderToAdd;
}

void OrderPool::modifyOrder(id_type idOrder, size_type size = 0){
    pool[idOrder].addSize(-size);
    if( pool[idOrder].getSize() == 0 ){
        pool.erase(idOrder);
    }
}

bool OrderPool::isEmpty(void) const{
    return pool.empty();
}

void OrderPool::printIds(void) const{
    for(auto items: pool){
        std::cout << items.first << std::endl;
    }
};
