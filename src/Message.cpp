#include "Message.hpp"

Message::Message(const std::string& _type,
    const id_type& _id,
    const time_type& _timestamp):
        type(_type),
        id(_id),
        timestamp(_timestamp){};

/**
 * Setter for the messegae. Transforms the Nasdaq type defintions in ours.
 *
 * - NASDAQ   --> Custom
 * - A,F      --> (A)dd
 * - D,X      --> (D)elete
 * - U        --> (R)eplace
 * - E        --> (E)xecution
 * - P        --> P, hidden execution
 * - C        --> C, execution at different price
 *
 * @param[in] _type type string: according to the definition of NASDAQ
 */
void Message::setType(const std::string& _type){
    if(_type =="A" || _type == "F"){
        // Messages related to adding new order.
        // The only difference between them:
        // "A"  - The market participant behind the order is anonymous.
        // "F"  - ID of the market participant behind the order is available
        // The information is irrelevant therefore we do not distinguish between them.
        type = "A"; // (A)dd
    }
    else if (_type == "D" || _type == "X"){
        // Messages related to cancellation of the order:
        // "D" - complete cancellation; the order related to this message has to be deleted from the book
        // "X" - partial cancellation
        type = "D"; // (D)elete
    }
    else if (_type == "U"){
        // The message is sent whenever existing order has been completelly canceled and replaced by the new one.
        type = "R"; // (R)eplace
    }
    else if (_type == "E"){
        // The message is sent whenever an order on the book is executed in whole or in part.
        type = _type; // (E)xecute
    }
    else if (_type == "P"){
        // The message indicates when a match occurs between non-­­displayable order types.
        // Since no Add Order Message is generated when a non-­displayed order is initially received
        // it does not affect the book.
        type = _type; // execute hidden message
    }
    else if (_type == "C"){
        // The message is sent whenever an order on the book is executed
        // in whole or in part at a price different from the initial display price.
        type = _type;
    }
    else{
        std::cerr << "Message with wrong type (" << _type << ") has been found!"<< std::endl;
    }
}

void Message::setId(const id_type& _id){
    id = _id;
}

void Message::setTimeStamp(const time_type& _timestamp){
    timestamp = _timestamp;
}

void Message::setSide(const side_type& _side){
    side = _side;
}

void Message::setPrice(const price_type& _price){
    price = _price;
}

void Message::setRemSize(const size_type& _size){
    remSize = _size;
}

void Message::setCancSize(const size_type& _size){
    cancSize = _size;
}

void Message::setExecSize(const size_type& _size){
    execSize = _size;
}

void Message::setOldId(const id_type& _id){
    oldId = _id;
}

void Message::setOldPrice(const price_type& _price){
    oldPrice = _price;
}

void Message::setOldSize(const size_type& _size){
    oldSize = _size;
}

// getters
std::string Message::getType() const{
    return type;
}

id_type Message::getId() const{
    return id;
}

time_type Message::getTimeStamp()const{
    return timestamp;
}

side_type Message::getSide()const{
    return side;
}

price_type Message::getPrice()const{
    return price;
}

size_type Message::getRemSize()const{
    return remSize;
}

size_type Message::getCancSize()const{
    return cancSize;
}

size_type Message::getExecSize()const{
    return execSize;
}

id_type Message::getOldId()const{
    return oldId;
}

price_type Message::getOldPrice()const{
    return oldPrice;
}

size_type Message::getOldSize()const{
    return oldSize;
}

bool Message::isEmpty()const{
    return (id==ID_DEFAULT);
}

/**
 * Get string representation for writing into the csv
 *
 * @return string representation of message.
 *          If field is not being setted is just an empty char
 *          separated by commas.
 *
 */
std::string Message::getString(void)const{
    std::ostringstream string_builder;
    if(!isEmpty()){
        string_builder  << timestamp << ",";
    }
    else{
        string_builder  << ",";
    }

    if(!isEmpty()){
        string_builder  << type  << ","
                        << id << ","
                        << side << ",";
    }
    else{
        string_builder  << ","
                        << ","
                        << ",";
    }
    if(remSize!=SIZE_DEFAULT){
        string_builder << remSize;
    }
    string_builder << ",";

    if(price!=PRICE_DEFAULT){
        string_builder << price;
    }
    string_builder << ",";

    if(cancSize!=SIZE_DEFAULT){
        string_builder << cancSize;
    }
    string_builder << ",";

    if(execSize!=SIZE_DEFAULT){
        string_builder << execSize;
    }
    string_builder << ",";

    if(oldId!=ID_DEFAULT){
        string_builder << oldId;
    }
    string_builder << ",";

    if(oldSize!=SIZE_DEFAULT){
        string_builder << oldSize;
    }
    string_builder << ",";

    if(oldPrice!=PRICE_DEFAULT){
        string_builder << oldPrice;
    }
    string_builder << std::endl;

    return string_builder.str();
}

void Message::print() const {
    std::cout << "Message type   :" << type <<std::endl;
    std::cout << "Id             :"<< id << std::endl;
    std::cout << "timestamp      :" << timestamp << std::endl;
    std::cout << "Side           :" << side << std::endl;
    std::cout << "Price          :"<< price << std::endl;
    std::cout << "Remaining size :" << remSize << std::endl;
    if (type == "D"){
        std::cout << "Deletion size  :" << cancSize << std::endl;
    }
    if (type == "E"){
        std::cout << "Execution size :" << execSize << std::endl;
    }
    if (type == "U"){
        std::cout << "Old Id         :" << oldId << std::endl;
        std::cout << "Old size       :"<< oldSize << std::endl;
        std::cout << "Old price      :" << oldPrice << std::endl;
    }
    std::cout << " " << std::endl;
}
