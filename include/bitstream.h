#ifndef SUS_BITSTREAM_H_
#define SUS_BITSTREAM_H_

#include "versioning.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bitstream_t bitstream_t;

/**
 * @brief Wraps an open file with a bitstream object.
 * 
 * @param file The file to wrap.
 * @param write Access direction. True to write to the file, false to read from file.
 * @return bitstream_t* The newly created bitstream or NULL if errored.
 */
bitstream_t *bitstream_create(FILE *file, bool write);
/**
 * @brief Writes to a bitstream, possibly also writing to the underlying file.
 * 
 * @param stream The bitstream to write to.
 * @param value The bit values to write to the stream.
 * @param bits The number of bits to write. Limited to a maximum 64.
 * @return int Error code for the operation.
 */
int bitstream_write(bitstream_t *stream, uint64_t value, int bits);
/**
 * @brief Reads from a bitstream, possibly reading from the underlying stream if needed.
 * 
 * @param stream The stream to read from.
 * @param store The destination of the read data.
 * @param bits The number of bits to read. Limited to a maximum of 64.
 * @return int Error code for the operation.
 */
int bitstream_read(bitstream_t *stream, uint64_t *store, int bits);
/**
 * @brief Closes a bitstream and frees associated memory, flushing any buffered data.
 * 
 * @param stream The bitstream to close.
 * @return int Error code for the operation.
 * 
 * @remark Does not close the underlying file.
 */
int bitstream_destroy(bitstream_t *stream);

#endif
