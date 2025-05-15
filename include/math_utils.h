#ifndef SUS_MATH_UTILS_H_
#define SUS_MATH_UTILS_H_

#include "versioning.h"

/**
 * @brief Determines the highest value of the two.
 * 
 */
#define MAX(a,b) ((a) < (b) ? (b) : (a))
/**
 * @brief Determines the lowest value of the two.
 * 
 */
#define MIN(a,b) ((a) > (b) ? (b) : (a))

/**
 * @brief Integer division with roundup.
 * 
 */
#define DIV_CEIL(a, b) ((((a) + (b) - 1) / (b)))

#endif
