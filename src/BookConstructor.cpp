#include <BookConstructor.hpp>

/**
 * Class Initializer.
 *
 * Principal class for the reconstruction of the order book.
 * The constructor also writes the headers to the output files.
 *
 * @param[in] inputMessageCSV decompressed binary ITCH50 file to read from.
 * @param[in] _stock selected stock.
 * @param[in] _levels selected number of levels for order book.
 * @param[out] outputBookCSV, outputMessageCSV destination files to write order book and stream message.
 */
BookConstructor::BookConstructor(const std::string &inputMessageCSV,
    const std::string &outputMessageCSV,
    const std::string &outputBookCSV,
    const std::string &_stock,
    const size_t &_levels):
    message_reader(inputMessageCSV, _stock),
    messageWriter(outputMessageCSV),
    bookWriter(outputBookCSV),
    levels(_levels){
        messageWriter.writeLine("time,type,id,side,size,price,cancSize,execSize,oldId,oldSize,oldPrice\n");
        std::string bookHeader = "time,";
        for(size_t i = 1; i<=levels; i++){
            std::string num = std::to_string(i);
            bookHeader += num+"_bid_price,"+num+"_bid_vol,"+num+"_ask_price,"+num+"_ask_vol,";
        }
        bookWriter.writeLine(bookHeader.substr(0, bookHeader.size()-1)+'\n');
    }

/**
 * Class deconstructor.
 *
 * For debug purposes print to std output orders still present at closure. There shouldn't be any.
 */
BookConstructor::~BookConstructor(){
    if(!pool.isEmpty()){
        std::cout << "Id's of orders remaining in the book after the market closure: ";
        pool.printIds();
    }
}

/**
 * Start Book reconstruction.
 *
 * calls iteratevely the next method untile the Reader has completed the reading.
 */
void BookConstructor::start(void){
    while(!message_reader.eof() and message_reader.isValid()){
        next();
    }
}

/**
 * Process next message. Retain only message affecting the OrderBook (type A,P,D,R,E,C).
 * Reads the message from the Reader interface then if necessary, complete message information retriving information from OrderPool, then updates the OrderBook and OrderPool according to the type of message recived.
 * At the end the Writer writes the book and message (enriched with all additional information) to the two output files.
 *
 */
void BookConstructor::next(){
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

/**
 * Complete message information with missing field.
 *
 * Once a message is readed by the reader this metod retrives missing informations from the
 * order pool, this behaviour depends on the type of the message.
 * Example : Execution messages miss Price -> retrieve order price from the OP through order ID.
 *
 * A,P: all the informations are already present, stop.
 * D: size and price information have to be retrived from the Pool.
 * R: oldSize and oldPrice information have to be retrived from the Pool.
 * E: size and price have to be retrived from the Pool.
 * C: size and original price have to be retrived from the Order Pool.
 *
 */
bool BookConstructor::updateMessage(void){
    std::string typeMsg = message.getType();

    if(typeMsg == "A" or typeMsg == "P"){
        return TRUE;
    }

    // Matching (R)eplace message is done by comparing its oldID with the IDs of preceding processed messages.
    id_type messageId = (typeMsg == "R") ? message.getOldId() : message.getId();

    // Find order in pool corresponding to the same ID as currently processing message.
    Order matchedOrder = pool.searchOrderPool(messageId);
    if(matchedOrder.isEmpty()){
        return FALSE;
    }

    message.setSide(matchedOrder.getSide());

    if(typeMsg == "D"){
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
        message.setOldSize(matchedOrder.getSize());
        message.setOldPrice(matchedOrder.getPrice());
    }

    else if(typeMsg == "E"){
        message.setPrice(matchedOrder.getPrice());
        size_type remainingSize = matchedOrder.getSize() - message.getExecSize();
        message.setRemSize(remainingSize);
    }

    else if(typeMsg == "C"){
        size_type remainingSize = matchedOrder.getSize() - message.getExecSize();
        message.setRemSize(remainingSize);
        message.setOldPrice(matchedOrder.getPrice());
    }

    else{
        std::cerr << "Unexpected type of message has been found while updating message! " << typeMsg << std::endl;
        return FALSE;
    }
    return TRUE;
}

/**
 * Update OrderBook with the current message.
 *
 * Updates the OrderBook double map accordingly to the type of the message.
 * A: Add the Order to the pool. If key in the map (price) is already there just add the size. Otherwise add the key with corresponding size.
 * R: Replace existing order in the pool, hence cancel completely the existing size and create a new one.
 *
 */
void BookConstructor::updateBook(void){
    book.setTimeStamp(message.getTimeStamp());
    std::string typeMsg = message.getType();

    if(typeMsg == "A"){
        book.modifySize(message.getPrice(),message.getRemSize(),message.getSide());
    }
    else if(typeMsg == "R"){
        // Replace existing order in the pool.

        // Completely cancel the existing order.
        book.modifySize(message.getOldPrice(),-message.getOldSize(),message.getSide());
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
    else if(typeMsg=="P"){
        // Execute hidden order. It does not affect the book.
    }

    else{
        std::cerr << "Unexpected type of message has been found while updating book! " << typeMsg << std::endl;
    }

    if(!book.checkBookConsistency()){
        std::cerr << "There is a bid price greater than ask." << std::endl;
    }
}

/**
 * Update OrderPool with the current Message.
 *
 * Using the message attribute in the BookConstructor class updates the pool.
 * - A: Add order to OrderPool.
 * - R: Delete order and add new one.
 * - D: Delete (partially or totally) order.
 * - E: Execute (partially or totally) order.
 * - C: Execute order at different price.
 * - P: Execute hidden order. Does not affect the book.
 *
 */
void BookConstructor::updatePool(void){
    std::string typeMsg = message.getType();

    if(typeMsg == "A"){
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    else if(typeMsg=="R"){
        pool.modifyOrder(message.getOldId(), message.getOldSize());
        pool.addToOrderPool(message.getId(), message.getSide(), message.getRemSize(), message.getPrice());
    }
    else if(typeMsg=="D"){
        pool.modifyOrder(message.getId(), message.getCancSize());
    }
    else if(typeMsg=="E"){
        pool.modifyOrder(message.getId(), message.getExecSize());
    }
    else if(typeMsg=="C"){
        pool.modifyOrder(message.getId(), message.getExecSize());
    }
    else if(typeMsg=="P"){
    }
    else{
        std::cerr << "Unexpected type of message has been found while updating pool! " << typeMsg << std::endl;
    }
}

/**
 * Write in output OrderBook state and message stream through Writer class.
 *
 */
void BookConstructor::WriteBookAndMessage(void){
    bookWriter.writeLine(book.getString(levels));
    messageWriter.writeLine(message.getString());
}
