class BookConstructor{
    
    long timestamp;
    Message message;
    OrderBook book;
    OrderPool pool;
    Reader message_reader;
    Writer book_writer;
    Writer message_writer;

    public:
    BookConstructor(std::string inputMessageCSV, std::string outputMessageCSV, std::string outputBookCSV);
    void next(); // the next message is the main method in the program
    void WriteBookAndMessage;

}

class Writer{
    std::string fileName;
    std::ifstream file;
    public:
    std::string getLine(void);
}

class Reader{
    std::string fileName;
    std::ofstream file;
    public:
    writeLine(std::string stringToWrite);
}

class Message{
    // ...
}

class OrderBook{
    long timestamp;
    std::map<long,long> buySide;
    std::map<long,long> sellSide;
    public:
    // since this should be done at every time, 
    // the datastructure of buySide/sellSide sould 
    // be done accordingly (not sure map is the right one).
    std::string getStringRepresentation(void); // "bestBidPrice,bestBidSize,bestAskPrice,bestAskSize,..."
    void addOrder(long price, long size); // size also negative
}

class OrderPool{
    std::unordered_map<long,Order>;
    public:
    Order findOrderPool(long id);
    void addToOrderPool(Order);
}

class Order{
    long id;
    long size; // the LOBSTER report puts here size and remaning size. Dunno why.
    long price;
    public:
    addDize(long size); // also negative
}

















