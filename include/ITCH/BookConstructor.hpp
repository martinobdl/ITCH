#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include <ITCH/Message.hpp>
#include <ITCH/Order.hpp>
#include <ITCH/OrderPool.hpp>
#include <ITCH/OrderBook.hpp>
#include <ITCH/Reader.hpp>
#include <ITCH/Writer.hpp>

class BookConstructor{
private:
    Message message;
    OrderBook book;
    OrderPool pool;
    Reader message_reader;
    Writer messageWriter;
    Writer bookWriter;
    Writer parserWriter;
    size_t levels;
public:
    BookConstructor(const std::string &inputMessageCSV,
                    const std::string &outputMessageCSV,
                    const std::string &outputBookCSV,
                    const std::string &_stock,
                    const size_t &_levels,
                    const bool debug);
    ~BookConstructor();
    void next();
    void WriteBookAndMessage();
    bool updateMessage();
    void updateBook();
    void updatePool();
    void start();
};

#endif
