#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include <Message.hpp>
#include <Order.hpp>
#include <OrderPool.hpp>
#include <OrderBook.hpp>
#include <Reader.hpp>
#include <Writer.hpp>


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
                    const size_t &_levels);
    ~BookConstructor();
    void start(void); 
    void next(void); // Processing a single line from input file.
    bool updateMessage(void);
    void updateBook(void);
    void updatePool(void);
    void WriteBookAndMessage(void);
};

#endif /* BOOKCONSTRUCTOR_H_ */
