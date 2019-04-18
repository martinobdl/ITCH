#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Reader.hpp>
#include <Message.hpp>
#include <Writer.hpp>

class MockReader: public Reader{
public:
    MOCK_METHOD1(readBytesIntoMessage, void(const long &size));
    MOCK_METHOD0(getKey, char());
    MockReader(const std::string &s):Reader(s){};
    void mock_readBytes_A(){
        setMessage("\x00\x00\x00\x00\x1a\x31\x86\x2d\xb8\x83\x00\x00\x00\x00\x00\x00\xb2\xb5\x53\x00\x00\x00\x5d\x4d\x41\x52\x54\x49\x4e\x4f\x20\x00\x01\xcc\x8c");
    }
    void mock_readBytes_E(){
        setMessage("\x00\x00\x00\x00\x1f\x1b\x50\x4f\xbd\x72\x00\x00\x00\x00\x00\x03\xfd\x79\x00\x00\x00\xc8\x5d\x50\x4b\x47\x20\x20\x20\x20\x20\x00\x01\xcc\x8c");
    }
    void mock_readBytes_X(){
        setMessage("\x00\x00\x00\x00\xff\xff\xff\xff\xff\xfe\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff\xff\xfe");
    }
    void mock_readBytes_D(){
        setMessage("\x00\x00\x00\x00\xff\xff\xff\xff\xff\xfe\xff\xff\xff\xff\xff\xff\xff\xfe");
    }
    void mock_readBytes_U(){
        setMessage("\x00\x00\x00\x00\x01\x00\x00\x00\x00\xff\x00\x00\x01\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x01\x00\x00\x2a\xf8");
    }
    void mock_readBytes_P(){
        setMessage("\x00\x00\x00\x00\x01\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\xff\x53\x00\x00\x00\xff\x4d\x41\x52\x54\x49\x4e\x4f\x20\x00\x00\x19\x80\x00\x00\x01\x00\x00\x00\x2a\xf8\x00\x00\x00\x00\x00\x00\x00\x00");
    }
};

struct Reader_Test : public testing::Test{
    MockReader *mk_reader;
    void SetUp(){
        mk_reader = new MockReader("MARTINO ");
    }
    void TearDown(){
        delete mk_reader;
    }
};

TEST_F(Reader_Test, conversion_A_F) {
    // Arrange
    EXPECT_CALL((*mk_reader), getKey())
    .Times(1)
    .WillOnce(testing::Return('A'));

    EXPECT_CALL((*mk_reader), readBytesIntoMessage(testing::_))
    .Times(1)
    .WillOnce(testing::InvokeWithoutArgs(&(*mk_reader), &MockReader::mock_readBytes_A));

    // Act
    Message createdMsg = mk_reader->createMessage();
    // Assert
    ASSERT_EQ("A,28800006862979,45749,1,93,11.79,,,,,\n",createdMsg.getString());
}

TEST_F(Reader_Test, conversion_E) {
    // Arrange
    EXPECT_CALL((*mk_reader), getKey())
    .Times(1)
    .WillOnce(testing::Return('E'));

    EXPECT_CALL((*mk_reader), readBytesIntoMessage(testing::_))
    .Times(1)
    .WillOnce(testing::InvokeWithoutArgs(&(*mk_reader), &MockReader::mock_readBytes_E));

    // Act
    Message createdMsg = mk_reader->createMessage();
    // Assert
    ASSERT_EQ("E,34202171981170,261497,0,,,,200,,,\n",createdMsg.getString());
}

TEST_F(Reader_Test, conversion_X) {
    // Arrange
    EXPECT_CALL((*mk_reader), getKey())
    .Times(1)
    .WillOnce(testing::Return('X'));

    EXPECT_CALL((*mk_reader), readBytesIntoMessage(testing::_))
    .Times(1)
    .WillOnce(testing::InvokeWithoutArgs(&(*mk_reader), &MockReader::mock_readBytes_X));

    // Act
    Message createdMsg = mk_reader->createMessage();
    // Assert
    ASSERT_EQ("D,281474976710654,18446744073709551614,0,,,4294967294,,,,\n",createdMsg.getString());
}

TEST_F(Reader_Test, conversion_D) {
    // Arrange
    EXPECT_CALL((*mk_reader), getKey())
    .Times(1)
    .WillOnce(testing::Return('U'));

    EXPECT_CALL((*mk_reader), readBytesIntoMessage(testing::_))
    .Times(1)
    .WillOnce(testing::InvokeWithoutArgs(&(*mk_reader), &MockReader::mock_readBytes_U));

    // Act
    Message createdMsg = mk_reader->createMessage();
    // Assert
    ASSERT_EQ("R,1099511628031,255,0,1,1.1,,,1099511628031,,\n",createdMsg.getString());
}

TEST_F(Reader_Test, conversion_P) {
    // Arrange
    EXPECT_CALL((*mk_reader), getKey())
    .Times(1)
    .WillOnce(testing::Return('P'));

    EXPECT_CALL((*mk_reader), readBytesIntoMessage(testing::_))
    .Times(1)
    .WillOnce(testing::InvokeWithoutArgs(&(*mk_reader), &MockReader::mock_readBytes_P));

    // Act
    Message createdMsg = mk_reader->createMessage();
    // Assert
    ASSERT_EQ("P,1099511628031,255,1,,0.6528,,255,,,\n",createdMsg.getString());
}
