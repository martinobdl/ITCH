#include <iostream>
#include "../c++/OrderPool.hpp"
#include "../c++/Order.hpp"
#include "../c++/Message.hpp"
#include "../c++/utility.hpp"

int main(){
  OrderPool pool;
  id_type id=1;
  bool side=true;
  size_type size=40;
  price_type price=30;

  Order found;
  pool.addToOrderPool(id, side, size, price);
  pool.addToOrderPool(23, false, 50, 40);
  found=pool.findOrderPool(23);
  found.print();

  pool.modifyOrder(23, 50);
  found=pool.findOrderPool(23);
  found.print();

  Message msg;
  std::cout<< msg.isEmpty()<<std::endl;
  return 0;
};
