#ifndef BOOKCONSTRUCTOR_H_
#define BOOKCONSTRUCTOR_H_

#include 

class BookConstructor{
    long timestamp;
    Message message;
    OrderBook book;
    OrderPool pool;
    Reader message_reader;
    Writer book_writer;
    Writer message_writer;
    std::string Stock;

    public:
    BookConstructor(std::string inputMessageCSV, std::string outputMessageCSV, std::string outputBookCSV,     std::string Stock);
    void next(); 
    void WriteBookAndMessage();
    void updateMessage(const std::string &s);
    void updateBook();
    void updatePool();
    void start();
}

#endif
