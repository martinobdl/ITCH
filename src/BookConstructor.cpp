#include <BookConstructor.hpp>

BookConstructor::BookConstructor(const std::string &inputMessageCSV,
    const std::string &outputMessageCSV,
    const std::string &outputBookCSV,
    const std::string &_stock,
    const size_t &_levels):
    message_reader(inputMessageCSV, _stock),
    messageWriter(outputMessageCSV),
    bookWriter(outputBookCSV),
    levels(_levels){
        // Write headers of output files.
        messageWriter.writeLine("time,type,id,side,size,price,cancSize,execSize,oldId,oldSize,oldPrice\n");
        std::string bookHeader = "time,";
        for(size_t i = 1; i<=levels; i++){
            std::string num = std::to_string(i);
            bookHeader += num+"_bid_price,"+num+"_bid_vol,"+num+"_ask_price,"+num+"_ask_vol,";
        }
        bookWriter.writeLine(bookHeader.substr(0, bookHeader.size()-1)+'\n');
    }

BookConstructor::~BookConstructor(){
    if(!pool.isEmpty()){
        std::cout << "Ids of orders remaining in the book after the market closure: ";
        pool.printIds();
    }
}

void BookConstructor::start(void){
    while(!message_reader.eof() and message_reader.isGood()){
        next();
    }
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

bool BookConstructor::updateMessage(void){
    std::string typeMsg = message.getType();

    if(typeMsg == "A" or typeMsg == "P"){
        // All information about the message has been read from input file.
        return 1;
    }

    // The information about other type of messages has to be recovered from preceding processed messages with same ID.
    // Matching (R)eplace message is done by comparing its oldID with the IDs of preceding processed messages.
    id_type messageId = (typeMsg == "R") ? message.getOldId() : message.getId();

    // Find order in pool corresponding to the same ID as currently processing message.
    Order matchedOrder = pool.searchOrderPool(messageId);
    if(matchedOrder.isEmpty()){
        return 0;
    }

    message.setSide(matchedOrder.getSide());

    if(typeMsg == "D"){
       // (D)elete: adding remSize, Price
        if (message.getCancSize() == SIZE_DEFAULT){
            // CancSize has default value, meaning the complete deletion has taken place.
            // Retrive the information about size to be canceled from matched order.
            message.setCancSize(matchedOrder.getSize());
        }

        size_type remainingSize = matchedOrder.getSize() - message.getCancSize();
        message.setRemSize(remainingSize);
        message.setPrice(matchedOrder.getPrice());
    }

    else if(typeMsg == "R"){
        // (R)eplace: adding oldSize, oldPrice
        message.setOldSize(matchedOrder.getSize());
        message.setOldPrice(matchedOrder.getPrice());
    }

    else if(typeMsg == "E"){
        // (E)xecution: adding remSize, price
        message.setPrice(matchedOrder.getPrice());
        size_type remainingSize = matchedOrder.getSize() - message.getExecSize();
        message.setRemSize(remainingSize);
    }

    else if(typeMsg == "C"){
        // Execution at different price
        size_type remainingSize = matchedOrder.getSize() - message.getExecSize();
        message.setRemSize(remainingSize);
        message.setOldPrice(matchedOrder.getPrice());
    }

    else{
        std::cerr << "Unexpected type of message has been found while updating message! " << typeMsg << std::endl;
        return 0;
    }
    return 1;
}

void BookConstructor::updateBook(void){
    book.setTimeStamp(message.getTimeStamp());
    std::string typeMsg = message.getType();

    if(typeMsg == "A"){
        // Add the order to the pool. If key in the map (price) is already there
        // just add the size. Otherwise add the key with corresponding size.
        book.modifySize(message.getPrice(),message.getRemSize(),message.getSide());
    }
    else if(typeMsg == "R"){
        // Replace existing order in the pool.
        //
        // Completely cancel the existing order.
        book.modifySize(message.getOldPrice(),-message.getOldSize(),message.getSide());
        //
        // Add new order.
        book.modifySize(message.getPrice(),message.getRemSize(),message.getSide());
    }
    else if(typeMsg == "D"){
        // Cancel order. Totally or partially.
        book.modifySize(message.getPrice(),-message.getCancSize(),message.getSide());
    }
    else if(typeMsg == "E"){
        // Execute order.
        book.modifySize(message.getPrice(),-message.getExecSize(),message.getSide());
    }
    else if(typeMsg == "C"){
        // Execute order at different price.
        book.modifySize(message.getOldPrice(),-message.getExecSize(),message.getSide());
    }

    else{
        std::cerr << "Unexpected type of message has been found while updating book! " << typeMsg << std::endl;
    }

    if(!book.checkBookConsistency()){
        std::cerr << "There is a bid price greater than ask." << std::endl;
    }
}

void BookConstructor::updatePool(void){
    std::string typeMsg = message.getType();

    if(typeMsg == "A"){
        // Add order to order pool.
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    else if(typeMsg=="R"){
        // Delete old order and add new one.
        pool.modifyOrder(message.getOldId(), message.getOldSize());
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    else if(typeMsg=="D"){
        // Delete (partially or totally) order.
        pool.modifyOrder(message.getId(), message.getCancSize());
    }
    else if(typeMsg=="E"){
        // Execute (partially or totally) order.
        pool.modifyOrder(message.getId(), message.getExecSize());
    }
    else if(typeMsg=="C"){
        // Execute order at different price.
        pool.modifyOrder(message.getId(), message.getExecSize());
    }
    else{
        std::cerr << "Unexpected type of message has been found while updating pool! " << typeMsg << std::endl;
    }
}

void BookConstructor::WriteBookAndMessage(void){
    bookWriter.writeLine(book.getString(levels));
    messageWriter.writeLine(message.getString());
}

