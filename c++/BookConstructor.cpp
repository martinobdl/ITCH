#include "BookConstructor.hpp"

BookConstructor::BookConstructor(const std::string &inputMessageCSV,
    const std::string &outputMessageCSV,
    const std::string &outputBookCSV,
    const std::string &_stock,
    const unsigned &_levels):
    message_reader(inputMessageCSV, _stock),
    messageWriter(outputMessageCSV),
    bookWriter(outputBookCSV),
    levels(_levels){
        messageWriter.writeLine("type,time,id,side,size,price,cancSize,execSize,oldId,oldSize,oldPrice\n");
    }

void BookConstructor::next(void){
    message = message_reader.createMessage();
    if(!message.isEmpty()){
        bool validMessage = updateMessage();
        if(validMessage){
            updatePool();
            updateBook();
            WriteBookAndMessage();
        }
    }
}

bool BookConstructor::updateMessage(){

    std::string typeMsg = message.getType();

    if(typeMsg == "A"){
        return 1;
    }
    // If we have "(R)eplace" message, we are searching the order oldId.
    id_type messageId = (typeMsg == "R") ? message.getOldId() : message.getId();

    // Find message in pool.
    Order order = pool.findOrderPool(messageId);
    if(order.isEmpty()){
        return 0;
    }
    message.setSide(order.getSide());

    if(typeMsg == "D"){
       // (D)elete: adding remSize, Price
        if (message.getCancSize() == 0){ // ???? change condition accordingly to if the default value is 0 or NaN (but it should be NaN :D)
            // We do not have CancSize hence we are in complete deletion of order.
            message.setCancSize(order.getSize());
        }

        size_type remainingSize = order.getSize() - message.getCancSize();
        message.setRemSize(remainingSize);
        message.setPrice(order.getPrice());
    }

    else if(typeMsg == "R"){
        //(R)eplace: adding oldSize, oldPrice
        message.setOldSize(order.getSize());
        message.setOldPrice(order.getPrice());
    }


    else if(typeMsg == "E"){
        //(E)xecution: adding remSize, price
        message.setPrice(order.getPrice());
        size_type remainingSize = order.getSize() - message.getExecSize();
        message.setRemSize(remainingSize);
    }

    else
        std::cerr << "Unexpected type found! " << typeMsg << std::endl;
    return 1;
}

void BookConstructor::updateBook(){
    book.setTimeStamp(message.getTimeStamp());
    std::string typeMsg = message.getType();
    if(typeMsg=="A"){
        // Add the order to the pool. If key in the map is already there
        // just add the size. Otherwise add the key with corresponding size.
        // Whatever side of the book I'm looking at.
        book.modifySize(message.getPrice(),message.getRemSize(),message.getSide());
    }
    if(typeMsg=="R"){
        // Take away the corrisponding size and add a new order.
        //
        // cancel.
        book.modifySize(message.getOldPrice(),-message.getOldSize(),message.getSide());
        //
        // add.
        book.modifySize(message.getPrice(),message.getRemSize(),message.getSide());
    }
    if(typeMsg=="D"){
        // Cancel order. Totally or partially.
        book.modifySize(message.getPrice(),-message.getCancSize(),message.getSide());
    }
    if(typeMsg=="E"){
        // Execute order.
        book.modifySize(message.getPrice(),-message.getExecSize(),message.getSide());
    }

}

void BookConstructor::updatePool(){
    std::string typeMsg = message.getType();
    if(typeMsg=="A"){
        // Add order to to order pool.
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    if(typeMsg=="R"){
        // Delete old order and add new one.
        pool.modifyOrder(message.getOldId(), message.getOldSize());
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    if(typeMsg=="D"){
        // Deleat partially or totally
        pool.modifyOrder(message.getId(), message.getCancSize());
    }
    if(typeMsg=="E"){
        // Take out parto of total size of order.
        pool.modifyOrder(message.getId(), message.getExecSize());
    }
}

void BookConstructor::WriteBookAndMessage(){
    bookWriter.writeLine(book.getString(levels));
    messageWriter.writeLine(message.getString());
}

void BookConstructor::start(){
    while(!message_reader.eof()){
        next();
    }
}
