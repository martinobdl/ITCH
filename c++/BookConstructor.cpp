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

    // find order corresponding to id of msg 
    Order foundOrder = pool.findOrderPool(msg.getID());
    msg.setSide(foundOrder.getSide());

    // then split into different cases depending on type
    if(typeMsg == "D"){
       //remSize, Price 
        if (msg.getCancSize() == 0 ) // ???? change condition accordingly to if the default value is 0 or NaN (but it should be NaN :D) 
            // we didnt set up CancSize meaning we are in complete deletion of order 
            msg.setCancSize(foundOrder.getSize()); 

        long remainingSize = foundOrder.getSize() - msg.getCancSize();
        msg.setRemSize(remainingSize); 
        msg.setPrice(foundOrder.getPrice());
    }

    else if(typeMsg == "R"){
        //oldSize, oldPrice
        msg.setOldSize(foundOrder.getSize());
        msg.setOldPrice(foundOrder.getPrice());
    }


    else{
        //execution: remSize, price
        msg.setPrice(foundOrder.getPrice());
        long remainingSize = foundOrder.getSize() - msg.getExecSize();
        msg.setRemSize(remainingSize);
    }   


    void updateBook(){

    }
    void updatePool(){

    }
}


