#include "utility.hpp"

std::string NAN_STR = "";
id_type ID_DEFAULT = -1;
price_type PRICE_DEFAULT = -1;
size_type SIZE_DEFAULT = -1;

long stringConvert(std::string input, the_type<long> ){
    long ret=std::stol(input);
    //std::cout<<"It's a long";
    return ret;
}

double stringConvert(std::string input, the_type<double> ){
    double ret=std::stod(input);
    //std::cout<<"It's a double";
    return ret;
}

long long stringConvert(std::string input, the_type<long long> ){
    long long ret=std::stoll(input);
    //std::cout<<"It's a long long";
    return ret;
}

float stringConvert(std::string input, the_type<float> ){
    float ret=std::stof(input);
    //std::cout<<"It's a float";
    return ret;
}
