#ifndef _Order_H_
#define _Order_H_


// type def for attributes ?
class Order{
    long id;
    bool side; // 0 for buy, 1 for sell
    long size; // the LOBSTER report puts here size and remaning size. Dunno why.
    long price;
    
    public:
    Order()=default;
    Order(const Message& ); // ??? is it better to pass message object or variable by variable
    Order(long, bool, long, long);
    void addSize(long size); // also negative

    //getters
    long getId() const;
    bool getSide() const;
    long getSize() const;
    long getPrice() const;
};



#endif /*_Order_H_*/