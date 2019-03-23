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

BookConstructor::updateMessage(Message &msg){
    std::string typeMsg = msg.getType();

    if(typeMsg == "A")
        return;

    // find id of msg then split into different cases depending on type
    if(typeMsg == "D"){
        // side, remSize, Price
    }

    else if(typeMsg == "R"){
        //side, oldSize, oldPrice
    }


    else{
        //execution: side, oldSize, oldPrice
    }   
}


