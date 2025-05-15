//sus.h - General definitions used throughout the library

#ifndef SUS_H_
#define SUS_H_

#include "versioning.h"

#define SUS_UNSIGNED_ERR (~(size_t)0)
#define SUS_BITSTREAM_ACCESS -8
#define SUS_INCOMPATIBLE_IVECTORS -7
#define SUS_INVALID_RANGE -6
#define SUS_ENTRY_NOT_FOUND -5
#define SUS_INVALID_INDEX -4
#define SUS_FAILED_ALLOC -3
#define SUS_INVALID_ARG -2
#define SUS_ERR -1
#define SUS_SUCCESS 0
#define SUS_FALSE 0
#define SUS_TRUE 1

/**
 * @brief Gets the string representation of a given error code.
 * 
 * @param error The error code to stringify.
 * @return const char* The string representation of the error code.
 */
const char *sus_strerror(int error);

#endif
