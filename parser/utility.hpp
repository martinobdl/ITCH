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


#define parse_stock(n) \
for (i=0; i<8; i++) { \
    stock[i] = m[i+(n)]; \
}

#define parse_issue_subtype(n) \
for (i=0; i<2; i++) { \
    issue_subtype[i] = m[i+(n)]; \
}

#define parse_reason(n) \
for (i=0; i<4; i++) { \
    reason[i] = m[i+(n)]; \
}

#define parse_mpid(n) \
for (i=0; i<4; i++) { \
    mpid[i] = m[i+(n)]; \
}

#define parse_attribution(n) \
for (i=0; i<4; i++) { \
    attribution[i] = m[i+(n)]; \
}

#endif
