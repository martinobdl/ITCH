#include "../c++/Writer.hpp"
#include "../c++/Message.hpp"
#include <string>

int main(){
  std::string output="outputfile.csv";
  Writer scrittore(output);
  scrittore.writeLine("Luigi, Martin, Ozrenka");
  scrittore.writeLine("aaaaaaaaaaaaaaaaaaaaaaaaaa");
  Message msg("A", 20, 4);
  scrittore.writeLine(msg.getstring());
  return 0;
}
