#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Order.hpp>
#include <utility.hpp>

struct Order_Test : public testing::Test{
    Order *emptyOrder;
    Order *fullOrder;
    void SetUp(){
        price_type price = 23;
        size_type size = 100;
        id_type id = 1234;
        side_type side = 0;
        emptyOrder = new Order();
        char mpid[] = "tmpd";
        fullOrder = new Order(id, side, size, price, mpid);
    }
    void TearDown(){
        delete emptyOrder;
        delete fullOrder;
    }
};

TEST_F(Order_Test, emptynessTest){
    ASSERT_EQ(1, emptyOrder->isEmpty());
}

TEST_F(Order_Test, fullnessTest){
    ASSERT_EQ(0, fullOrder->isEmpty());
}

TEST_F(Order_Test, negativeSizeTest){

    // act
    fullOrder->addSize(-75);

    // assert
    ASSERT_EQ(25, fullOrder->getSize());
}
