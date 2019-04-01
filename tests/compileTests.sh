#/!bin/bash

#g++ -std=c++11 OrderBookTest.cpp ../c++/OrderBook.cpp -o OrderBookTest.out
#g++ -std=c++11 MessageTest.cpp ../c++/Message.cpp ../c++/Reader.cpp -o MessageTest.out
#g++ -std=c++11 OrderPoolTest.cpp ../c++/OrderPool.cpp ../c++/Order.cpp -o OrderPoolTest.out
#g++ -std=c++11 WriterTest.cpp ../c++/Writer.cpp -o WriterTest.out
g++ -std=c++11 -Wfatal-errors BookConstructorTest.cpp ../c++/Message.cpp ../c++/BookConstructor.cpp ../c++/Writer.cpp ../c++/Reader.cpp ../c++/Order.cpp ../c++/OrderBook.cpp ../c++/OrderPool.cpp ../c++/utility.cpp -o BookConstructorTest.out
