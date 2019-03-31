#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include "Message.hpp"
#include "Order.hpp"
#include "OrderPool.hpp"
#include "OrderBook.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

class BookConstructor{
    long timestamp;
    Message message;
    OrderBook book;
    OrderPool pool;
    Reader message_reader;
    Writer bookWriter;
    Writer messageWriter;
    unsigned levels;

    public:
    BookConstructor(const std::string &inputMessageCSV,const std::string &outputMessageCSV, const std::string &outputBookCSV, const std::string &_stock, const unsigned &_levels);
    void next();
    void WriteBookAndMessage();
    bool updateMessage();
    void updateBook();
    void updatePool();
    void start();
};

#endif
