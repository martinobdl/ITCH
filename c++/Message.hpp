#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <limits>
#include <string>
#include <sstream>
#include <iostream>
#include "utility.hpp"

class Message{
private:
    std::string type = NAN_STR;
    id_type id=-1;
    time_type timestamp=0;

    side_type side;
    price_type price=-1;
    size_type remSize=-1;
    size_type cancSize=-1;
    size_type execSize=-1;

    id_type oldId = ID_DEFAULT;
    price_type oldPrice=-1;
    size_type oldSize=-1;

public:
    Message()=default;
    Message(const std::string& type,const id_type &id,
        const time_type &timestamp);
    void setType(const std::string &type);
    void setId(const id_type &id);
    void setTimeStamp(const time_type &timestamp);
    void setSide(const side_type &side);
    void setPrice(const price_type &price);
    void setRemSize(const size_type &size);
    void setCancSize(const size_type &size);
    void setExecSize(const size_type &size);
    void setOldId(const id_type &id);
    void setOldPrice(const price_type &price);
    void setOldSize(const size_type &size);

    // to be discussed if we need all of them:
    std::string getType() const;
    id_type getId() const;
    time_type getTimeStamp()const;
    side_type getSide()const;
    price_type getPrice()const;
    size_type getRemSize()const;
    size_type getCancSize()const;
    size_type getExecSize()const;
    id_type getOldId()const;
    price_type getOldPrice()const;
    size_type getOldSize()const;

    bool isEmpty()const;
    std::string getString()const;
    void print();
};
#endif/*_MESSAGE_H_*/
