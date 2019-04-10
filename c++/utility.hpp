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

#endif
