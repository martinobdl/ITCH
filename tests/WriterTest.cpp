#include "../c++/Writer.hpp"
#include <string>

int main(){
  std::string output="outputfile.csv";
  Writer scrittore(output);
  scrittore.writeLine("Luigi, Martin, Ozrenka");
  scrittore.writeLine("aaaaaaaaaaaaaaaaaaaaaaaaaa");
  return 0;
}
