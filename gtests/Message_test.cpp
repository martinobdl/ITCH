#include "../c++/Message.cpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct Message_Test : public testing::Test{
    Message *emptyMessage;
    Message *fullMessage;
    void SetUp(){
        emptyMessage = new Message();
        fullMessage = new Message("A",45749,28800006862979);
    }
    void TearDown(){
        delete emptyMessage;
        delete fullMessage;
    }
};

TEST_F(Message_Test, emptynessTest){
    ASSERT_EQ(1, emptyMessage->isEmpty());
}

TEST_F(Message_Test, getStringEmptyTest){
    fullMessage->setSide(1);
    fullMessage->setRemSize(93);
    fullMessage->setPrice(11.79);

    ASSERT_EQ(",,,,,,,,,,\n", emptyMessage->getString());
}

TEST_F(Message_Test, getStringFullTest){
    fullMessage->setSide(1);
    fullMessage->setRemSize(93);
    fullMessage->setPrice(11.79);

    ASSERT_EQ("A,28800006862979,45749,1,93,11.79,,,,,\n", fullMessage->getString());
}
