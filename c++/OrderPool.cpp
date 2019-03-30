#include "OrderPool.hpp"

// bool OrderPool::inPool(id_type idOrder){
// auto found=pool.find(idOrder);
// if (found!=pool.end()) return true;
// else{return false;}
// };


Order OrderPool::findOrderPool(id_type idOrder){
  auto found=pool.find(idOrder);
  Order ret;
  if (found!=pool.end()){
    ret=found->second;
  }else {std::cerr <<"Order did not found"<<std::endl;}
  return ret;
};

void OrderPool::addToOrderPool(id_type idOrder, bool side, size_type size, price_type price){
  Order orderToAdd(idOrder, side, size, price);
  pool[idOrder]=orderToAdd;
  return;
};

void OrderPool::modifyOrder(id_type idOrder, size_type size=0){
  if (size==0){
    pool.erase(idOrder);
    std::cout<<"size = 0"<<std::endl;
  }else{
    pool[idOrder].addSize(-size);
    if (pool[idOrder].getSize()==0) pool.erase(idOrder);
    };
  return;
};
