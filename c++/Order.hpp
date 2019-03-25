#ifndef _Order_H_
#define _Order_H_

class Order{
    long id;
    bool side; // 0 for buy, 1 for sell
    long size; // the LOBSTER report puts here size and remaning size. Dunno why.
    long price;
    
    public:
    Order()=default;
    Order(const Message& ); // ??? is it better to pass message object or variable by variable
    Order(long, bool, long, long);
    addSize(long size); // also negative
};



#endif /*_Order_H_*/