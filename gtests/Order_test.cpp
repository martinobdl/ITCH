#include "../c++/Order.cpp"
#include <gtest/gtest.h>

TEST(Order_test, basic){
    Order empty_order;
    price_type price = 23;
    size_type size = 100;
    id_type id = 1234;
    bool side = 0;
    Order full_order(id, side, size, price);

    ASSERT_EQ(1, empty_order.isEmpty());
    ASSERT_EQ(0, full_order.isEmpty());
    ASSERT_EQ(1234, full_order.getId());
    ASSERT_EQ(100, full_order.getSize());
    ASSERT_EQ(23, full_order.getPrice());

    full_order.addSize(50);

    ASSERT_EQ(150, full_order.getSize());

    full_order.addSize(-75);

    ASSERT_EQ(75, full_order.getSize());

    full_order.addSize(-75);

    ASSERT_EQ(0, full_order.getSize());

    ASSERT_EQ(0, full_order.isEmpty());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
