#ifndef _Message_H_
#define _Message_H_

#include <limits>
#include <string>
#include <sstream>
#include <iostream>

#include "utility.hpp"

class Message{
private:
  std::string type = NAN_STR;
  id_type id=-1;
  time_type timestamp=-1;

  bool side;
  price_type price=-1;
  size_type remSize=-1;
  size_type cancSize=-1;
  size_type execSize=-1;

  id_type oldId = ID_DEFAULT;
  price_type oldPrice=-1;
  size_type oldSize=-1;

public:
  Message()=default;
  Message(const std::string& type,const id_type &id,const long &timestamp);
  void setType(const std::string &type);
  void setId(const id_type &id);
  void setTimeStamp(const long &timestamp);
  void setSide(const bool &side);
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
  long getTimeStamp()const;
  bool getSide()const;
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
#endif/*_Message_H_*/
