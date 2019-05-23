#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <inttypes.h> // PRIux
#include <cstring>
#include <Message.hpp>
#include <Writer.hpp>

class Reader{
private:
    std::string fileName;
    std::ifstream file;
    // std::string messageToFilter = "AFEXDU"; // QC
    std::string stock;
    unsigned count = 0;
    char message[64];
    bool validFile = 0;
    time_t start;
    // bool debug = 0;
    // Writer parserWriter;
public:

    /**
     * Constructor for Reader class
     *
     * If unable to open file to read print to standard error a Message.
     * If file has been opened correctly, write it to standard optput.
     *
     * @param[in] _fileName destination csv files to update.
     * @param[in] _stock For performace reasons, the Reader class will discard directly all messages clearly related to other stocks
     */
    Reader(const std::string &fileName, const std::string &stock);

    /**
     * Alternative Constructor for Reader class
     *
     * Constructor used in tests where we do not need a fileName.
     *
     * @param[in] _stock For performace reasons, the Reader class will discard directly all messages clearly related to other stocks
     */
    Reader(const std::string &_stock);
    bool isValid(void) const;
    virtual ~Reader();

    /**
     * Reads bytes from the stream and create a message
     *
     * Main function of the class. Creates a Message object from the file stream and return a message to the BookConstructor class.
     *
     *@return Message created from the read bytes.
     *@warning Dead code is still present in the method. Might be used to parse the entire input ITCH50 file for debug purposes
     *
     */
    Message createMessage(void);
    bool eof(void);

    /**
     * Progress updates
     *
     * Writes to standard output a progress message with the number of messages analyzed up to now and average number of messages per second since the beginnning.
     *
     */
    void printProgress(void);

    /**
     * Reads n bytes from the opend file
     *
     * Reads from the file into the message c-string attribute of the Reader class the specified number of bytes.
     *
     *@params[in] size Number of bytes to read from the stream.
     *
     */
    virtual void readBytesIntoMessage(const long &);

    /**
     * Skips n bytes from the stream
     *
     * Discard from the file the specified number of bytes. Used mainly in the tests.
     *
     *@params[in] size Number of bytes to discard from the stream.
     *
     */
    virtual void skipBytes(const long &);
    void setMessage(const char*);
    virtual char getKey(void);
    std::string getFileName(void) const;
    std::string getStock(void) const;
};

#endif
