#include "utility.hpp"

std::vector<std::string> split(std::string str, const std::string &token){
    //
    // splits str wrt the string token
    // and returns a vector of strings
    //
    std::vector<std::string> result;
    while(str.size()>0){
        size_t index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0){
                result.push_back(str);
            }
        }
        else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}
