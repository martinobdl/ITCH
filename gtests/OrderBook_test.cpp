#include "../c++/OrderBook.cpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct OrderBook_Test : public testing::Test{
    OrderBook *book;
    void SetUp(){
        book = new OrderBook();
        book->setTimeStamp(123456789);
    }
    void TearDown(){
        delete book;
    }
};

TEST_F(OrderBook_Test, NoOrdersTest){
    ASSERT_EQ("123456789,,,,,,,,\n", book->getString(2));
}

TEST_F(OrderBook_Test, AddOrdersNotExisting){
    book->modifySize(99.99,123,0);
    book->modifySize(101.99,12,1);
    book->modifySize(105.99,12,1);
    ASSERT_EQ("123456789,99.99,123,101.99,12,,,105.99,12\n", book->getString(2));
}

TEST_F(OrderBook_Test, AddExistingOrders){
    book->modifySize(99.99,123,0);
    book->modifySize(101.99,12,1);
    book->modifySize(101.99,-11,1);
    book->modifySize(105.99,12,1);
    book->modifySize(105.99,-12,1);
    ASSERT_EQ("123456789,99.99,123,101.99,1,,,,\n", book->getString(2));
}
