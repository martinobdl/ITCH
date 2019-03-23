#ifndef _Message_H_
#define _Message_H_

#include <limits>
#include <string>

class Message{
public:
  typedef float price_type;
  typedef float size_type;
  typedef float id_type;

private:
  std::string type="";
  id_type id=0;
  long timestamp=0;

  bool side;
  price_type price=0.0;
  size_type size=0;
  size_type cancSize=0;
  size_type execSize=0;

  id_type oldId=std::numeric_limits<id_type>::signaling_NaN();
  price_type oldPrice=std::numeric_limits<price_type>::quiet_NaN();
  size_type oldSize=std::numeric_limits<size_type>::quiet_NaN();

public:
  Message()=default;
  Message(const std::string& type,const id_type &id,const long& timestamp);
  void setType(const std::string& type);
  void setId(const id_type& id);
  void setTimestamp(const long& timestamp);
  void setSide(const bool& side);
  void setPrice(const price_type& price);
  void setCancSize(const size_type& size);
  void setExecSize(const size_type& size);
  void setOldId(const id_type& id);
  void setOldPrice(const price_type& price);
  void setOldSize(const size_type& size);

  void print();

};
#endif/*_Message_H_*/
