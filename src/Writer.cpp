#include <Writer.hpp>

/**
 * Constructor for Writer class
 *
 * If unable to open file to read print to standard error a message.
 * If file has been opened correctly, write it to standard optput.
 *
 * @param[in] _fileName destination csv files to update.
 */
Writer::Writer(const std::string& _fileName):fileName(_fileName){
  file.open(_fileName);
  if(!file.is_open()){
      std::cerr << "The output file: " << fileName << " cannot be open! " << std::endl;
      }
  else {
      std::cout << "Opened " << fileName << " for writing." << std::endl;
  }
}

/**
 * Writes string to stream
 *
 * It used to write the Message and the OrderBook strings to the outfiles.
 * @param[in] stringToWrite string to write to the csv.
 */
void Writer::writeLine(const std::string &stringToWrite){
  file << stringToWrite;
}

Writer::~Writer(){
  if (file.is_open())
     {
         file.flush();
         file.close();
         std::cout << "File " << fileName << " has been closed." << std::endl;
    }
}

std::string Writer::getFileName(void) const{
  return fileName;
}
