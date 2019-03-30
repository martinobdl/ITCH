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
    std::string Stock;

    public:
    BookConstructor(std::string inputMessageCSV, std::string outputMessageCSV, std::string outputBookCSV,     std::string Stock);
    void next(); 
    void WriteBookAndMessage();
    bool updateMessage();
    void updateBook();
    void updatePool();
    void start();
};

#endif
