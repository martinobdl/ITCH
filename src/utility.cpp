#include <utility.hpp>

std::string NAN_STR = "";
id_type ID_DEFAULT = 72057594037927934;
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

uint16_t bswap_16(uint16_t value){
    return static_cast<uint16_t>(((value) & 0xff) << 8 | ((value) >> 8));
}

uint32_t bswap_32(uint32_t value){
    return ((static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) & 0xffff))) << 16) |
    static_cast<uint32_t>(bswap_16(static_cast<uint16_t>((value) >> 16))));
}

uint64_t bswap_64(uint64_t value){
    return ((static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) & 0xffffffff))) << 32) |
    static_cast<uint64_t>(bswap_32(static_cast<uint32_t>((value) >> 32))));
}

uint16_t parse_uint16(char * a){
    return bswap_16(*(reinterpret_cast<uint16_t *>(a)));
}

uint32_t parse_uint32(char * a){
    return bswap_32(*(reinterpret_cast<uint32_t *>(a)));
}

uint64_t parse_uint64(char * a){
    return bswap_64(*(reinterpret_cast<uint64_t *>(a)));
}

uint64_t parse_ts(char * a){
    return (((static_cast<uint64_t>(bswap_16(*(reinterpret_cast<uint16_t *>(a))))) << 32) |
    static_cast<uint64_t>(bswap_32(*(reinterpret_cast<uint32_t *>(a+2)))));
}
