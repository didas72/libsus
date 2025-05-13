#ifndef SUS_BITSTREAM_H_
#define SUS_BITSTREAM_H_

#include "versioning.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bitstream_t bitstream_t;

bitstream_t *bitstream_create(FILE *file, bool write);
int bitstream_write(bitstream_t *stream, uint64_t value, int bits);
int bitstream_read(bitstream_t *stream, uint64_t *store, int bits);
int bitstream_destroy(bitstream_t *stream);

#endif
