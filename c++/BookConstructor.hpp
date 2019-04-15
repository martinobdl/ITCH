#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include "Message.hpp"
#include "Order.hpp"
#include "OrderPool.hpp"
#include "OrderBook.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

class BookConstructor{
private:
    Message message;
    OrderBook book;
    OrderPool pool;
    Reader message_reader;
    Writer messageWriter;
    Writer bookWriter;
    size_t levels;
public:
    BookConstructor(const std::string &inputMessageCSV,
                    const std::string &outputMessageCSV,
                    const std::string &outputBookCSV,
                    const std::string &_stock,
                    const size_t &_levels);
    ~BookConstructor();
    void next();
    void WriteBookAndMessage();
    bool updateMessage();
    void updateBook();
    void updatePool();
    void start();
};

#endif
