#ifndef _Message_H_
#define _Message_H_

#include <limits>
#include <string>

class Message{
public:
  typedef double price_type;
  typedef double size_type;
  typedef double id_type;

private:
  std::string type="";
  id_type id=0;
  long timestamp=0;

  bool side;
  price_type price=0.0;
  size_type remSize=0;
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
  void setTimeStamp(const long& timestamp);
  void setSide(const bool& side);
  void setPrice(const price_type& price);
  void setRemSize(const size_type& size);
  void setCancSize(const size_type& size);
  void setExecSize(const size_type& size);
  void setOldId(const id_type& id);
  void setOldPrice(const price_type& price);
  void setOldSize(const size_type& size);

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



  void print();

};
#endif/*_Message_H_*/
