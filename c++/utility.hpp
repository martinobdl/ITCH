#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

typedef double price_type;
typedef long size_type;
typedef long id_type;
typedef long long time_type;
typedef bool side_type;

extern id_type ID_DEFAULT;
extern size_type SIZE_DEFAULT;
extern price_type PRICE_DEFAULT;
extern std::string NAN_STR;

template<class T>class the_type{};

long stringConvert(std::string input, the_type<long>);
double stringConvert(std::string input, the_type<double>);
long long stringConvert(std::string input, the_type<long long>);
float stringConvert(std::string input, the_type<float>);

uint16_t bswap_16(uint16_t value);
uint32_t bswap_32(uint32_t value);
uint64_t bswap_64(uint64_t value);
uint16_t parse_uint16(char * a);
uint32_t parse_uint32(char * a);
uint64_t parse_uint64(char * a);
uint64_t parse_ts(char * a);

#endif
