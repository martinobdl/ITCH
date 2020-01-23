#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <sstream>
#include <iostream>
#include <utility.hpp>

class Message{
private:
    char type = 0;
    id_type id = ID_DEFAULT;
    time_type timestamp = 0;

    side_type side = SIDE_DEFAULT;
    price_type price = PRICE_DEFAULT;
    size_type remSize = SIZE_DEFAULT;
    size_type cancSize = SIZE_DEFAULT;
    size_type execSize = SIZE_DEFAULT;

    id_type oldId = ID_DEFAULT;
    price_type oldPrice = PRICE_DEFAULT;
    size_type oldSize = SIZE_DEFAULT;
    char mpid[5] = "";

public:
    Message() = default;
    Message(const char& type,const id_type &id,
        const time_type &timestamp);

    /**
     * Setter for the message. Transforms the Nasdaq type definitions in ours.
     *
     * - NASDAQ   --> Custom
     * - A,F      --> (A)dd
     * - D,X      --> (D)elete
     * - U        --> (R)eplace
     * - E        --> (E)xecution
     * - P        --> P, hidden execution
     * - C        --> C, execution at different price
     *
     * @param[in] _type type string: according to the definition of NASDAQ
     */
    void setType(const char &);
    void setId(const id_type &);
    void setTimeStamp(const time_type &);
    void setSide(const side_type &);
    void setPrice(const price_type &);
    void setRemSize(const size_type &);
    void setCancSize(const size_type &);
    void setExecSize(const size_type &);
    void setOldId(const id_type &id);
    void setOldPrice(const price_type &);
    void setOldSize(const size_type &);
    void setMPID(const char &);

    char getType(void) const;
    id_type getId(void) const;
    time_type getTimeStamp(void) const;
    side_type getSide(void) const;
    price_type getPrice(void) const;
    size_type getRemSize(void) const;
    size_type getCancSize(void) const;
    size_type getExecSize(void) const;
    id_type getOldId(void) const;
    price_type getOldPrice(void) const;
    size_type getOldSize(void) const;
    const char *getMPID(void) const;

    bool isEmpty(void) const;

    /**
     * Get string representation for writing into the csv
     *
     * @return string representation of message.
     *          If field is not being setted it is just an empty char
     *          separated by commas.
     *
     */
    std::string getString(void) const;
    void print(void) const;
};


#endif/*_MESSAGE_H_*/
