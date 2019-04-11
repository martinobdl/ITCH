#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

uint16_t bswap_16(uint16_t value);
uint32_t bswap_32(uint32_t value);
uint64_t bswap_64(uint64_t value);
uint16_t parse_uint16(char * a);
uint32_t parse_uint32(char * a);
uint64_t parse_uint64(char * a);
uint64_t parse_ts(char * a);

#endif
