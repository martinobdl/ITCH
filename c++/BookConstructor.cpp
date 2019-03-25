#include "BookConstructor.cpp"

BookConstructor::BookConstructor(std::string inputMessageCSV, std::string outputMessageCSV, std::string outputBookCSV,std::string _Stock):message_reader(inputMessageCSV),message_writer(outputMessageCSV),book_writer(outputMessageCSV),Stock(_Stock){
    
}

BookConstructor::next(void){
    Message msg=message_reader.createMessage();
    updateMessage(msg);
    updatePool();
    updateBook();
    WriteBookAndMessage();
}

void BookConstructor::updateMessage(Message &msg){
    std::string typeMsg = msg.getType();

    if(typeMsg == "A")
        return;

    // if we have "replace" message, we are searching the order with id equal to old id
    id_type foundId = (typeMsg == "R") ? msg.getOldId() : msg.getId();
    
    // find order corresponding to id of msg 
    Order foundOrder = pool.findOrderPool(foundId);
    msg.setSide(foundOrder.getSide());

    // then split into different cases depending on type
    if(typeMsg == "D"){
       //delete: remSize, Price 
        if (msg.getCancSize() == 0 ) // ???? change condition accordingly to if the default value is 0 or NaN (but it should be NaN :D) 
            // we didnt set up CancSize meaning we are in complete deletion of order 
            msg.setCancSize(foundOrder.getSize()); 

        size_type remainingSize = foundOrder.getSize() - msg.getCancSize();
        msg.setRemSize(remainingSize); 
        msg.setPrice(foundOrder.getPrice());
    }

    else if(typeMsg == "R"){
        //replace: oldSize, oldPrice
        msg.setOldSize(foundOrder.getSize());
        msg.setOldPrice(foundOrder.getPrice());
    }


    else if(typeMsg == "E"){
        //execution: remSize, price
        msg.setPrice(foundOrder.getPrice());
        size_type remainingSize = foundOrder.getSize() - msg.getExecSize();
        msg.setRemSize(remainingSize);
    }   

    else
        std::cerr << "Unexpected type found! " << typeMsg << std::endl;
}

void BookConstructor::updateBook(){

    }
    
void BookConstructor::updatePool(){

    }



