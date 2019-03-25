#ifndef _OrderPool_H_
#define _OrderPool_H_

class OrderPool{
    std::unordered_map<long,Order>;
    
    public:
    Order findOrderPool(long id);
    void addToOrderPool(Order);
};



#endif /*_OrderPool_H_*/