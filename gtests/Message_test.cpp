#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Message.hpp>
#include <utility.hpp>

struct Message_Test : public testing::Test{
    Message *emptyMessage;
    Message *fullMessage;
    void SetUp(){
        emptyMessage = new Message();
        fullMessage = new Message('A',45749,28800006862979);
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

    ASSERT_EQ(",,,,,,,,,,,\n", emptyMessage->getString());
}

TEST_F(Message_Test, getStringAndSettersTest){
    const char mpid[] = "tmpd";
    fullMessage->setSide(1);
    fullMessage->setRemSize(93);
    fullMessage->setPrice(11.79);
    fullMessage->setCancSize(10);
    fullMessage->setExecSize(20);
    fullMessage->setOldId(123456);
    fullMessage->setOldSize(110);
    fullMessage->setOldPrice(33.333333);
    fullMessage->setMPID(*mpid);
    ASSERT_EQ("28800006862979,A,45749,1,93,11.79,10,20,123456,110,33.3333,tmpd\n", fullMessage->getString());
}

TEST_F(Message_Test, getMPIDTest){
    const char mpid[]="tmpd";
    fullMessage->setMPID(*mpid);
    std::string mpid_string(fullMessage->getMPID());
    ASSERT_EQ("tmpd", mpid_string);
}

TEST_F(Message_Test, getSetMPIDTest){
    const char mpid[]="tmpd";
    fullMessage->setMPID(*mpid);
    emptyMessage->setMPID(*fullMessage->getMPID());
    std::string mpid_string(emptyMessage->getMPID());
    ASSERT_EQ("tmpd", mpid_string);
}
