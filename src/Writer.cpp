#include <Writer.hpp>

Writer::Writer(const std::string& _fileName):fileName(_fileName){
  file.open(_fileName);
  if(!file.is_open()){
      std::cerr << "The output file: " << fileName << " cannot be open! " << std::endl;
      }
  else {
      std::cout << "Opened " << fileName << " for writing." << std::endl;
  }
}

void Writer::writeLine(std::string stringToWrite){
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
