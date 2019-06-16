#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <climits>
// #include <netinet/in.h>

/**
 * Declaration of default values.
 *
 * @file utility.cpp
 */

typedef double price_type;
typedef long size_type;
typedef uint64_t id_type;
typedef long long time_type;
typedef bool side_type;

extern id_type ID_DEFAULT;
extern side_type SIDE_DEFAULT;
extern size_type SIZE_DEFAULT;
extern price_type PRICE_DEFAULT;

/**
 * Utility function for swapping 16 bits from little endian to big endian format.
 *
 * Since the binary file is written in big endian and most Unix systems are little endian, we defined this utility functions to swap endianess. Uses binary masks to perform this operation.
 *
 * @param[in] value unsigned 16 type corresponding to the 16 bits in big endian to swap into little endian.
 * @return uint16_t value of the swapped number
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint16_t bswap_16(uint16_t value);

/**
 * Utility function for swapping 32 bits from little endian to big endian format.
 *
 * Since the bynary file is written in big endian and most Unix systems are little endian, we defined this utility functions to swap endianess. Uses binary masks to perform this operation.
 *
 * @param[in] value unsigned 16 type corresponding to the 32 bits in big endian to swap into little endian.
 * @return uint32_t value of the swapped number
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint32_t bswap_32(uint32_t value);

/**
 * Utility function for swapping 64 bits from little endian to big endian format.
 *
 * Since the bynary file is written in big endian and most Unix systems are little endian, we defined this utility functions to swap endianess. Uses binary masks to perform this operation.
 *
 * @param[in] value unsigned 64 type corresponding to the 64 bits in big endian to swap into little endian.
 * @return uint64_t value of the swapped number
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint64_t bswap_64(uint64_t value);

/**
 * Utility function for parsing 16 bits data.
 *
 * This reads from a char array pointer (C-style) 16 bits and return the swapped corresponding number
 *
 * @param[in] a char pointer to the 16 bits to parse
 * @return uint16_t number corresponding to the swapped data (16 bits) pointed by the char array
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint16_t parse_uint16(char * a);

/**
 * Utility function for parsing 32 bits data.
 *
 * This reads from a char array pointer (C-style) 32 bits and return the swapped corresponding number
 *
 * @param[in] a char pointer to the 32 bits to parse
 * @return uint32_t number corresponding to the swapped data (32 bits) pointed by the char array
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint32_t parse_uint32(char * a);

/**
 * Utility function for parsing 64 bits data.
 *
 * This reads from a char array pointer (C-style) 64 bits and return the swapped corresponding number
 *
 * @param[in] a char pointer to the 64 bits to parse
 * @return uint64_t number corresponding to the swapped data (64 bits) pointed by the char array
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint64_t parse_uint64(char * a);

/**
 * Utility function for parsing 48 bits data (for time stamp)
 *
 * This reads from a char array pointer (C-style) 48 bits and return the swapped correpsonding number
 *
 * @param[in] a char pointer to the 48 bits to parse
 * @return uint64_t number corresponding to the swapped data (48 bits) pointed by the char array
 * @warning Assumes that the machine is little endian and hence the swapping is indeed necessary. Otherwise no swapping is needed. This check is not performed.
 */
uint64_t parse_ts(char * a);

/**
 * Simple utility function for get the file name from a path string
 *
 * @param[in] path string of the path of the file. Should also work for the separator "\\" (WINDOWS).
 * @return nameFile string of the file name.
 */
std::string getFileName(const std::string& s);

#endif /* UTILITY_H_ */
