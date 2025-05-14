#include "bitstream.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sus.h"
#include "math_utils.h"

struct bitstream_t
{
	FILE *file;
	uint64_t buffer;
	int head;
	bool write;
};

bitstream_t *bitstream_create(FILE *file, bool write)
{
	bitstream_t *stream = malloc(sizeof(bitstream_t));
	if (!stream) return NULL;

	stream->file = file;
	stream->buffer = 0;
	stream->head = write ? 0 : 64;
	stream->write = write;

	return stream;
}
int bitstream_write(bitstream_t *stream, uint64_t value, int bits)
{
	if (!stream->write) return SUS_BITSTREAM_ACCESS;
	if (bits < 0 || bits > 64) return SUS_INVALID_ARG;

	int fbits = 64 - stream->head;

	if (bits >= fbits) //Needs flushing
	{
		uint64_t mask = ~(uint64_t)0 >> (64 - fbits);
		uint64_t masked = value & mask;
		stream->buffer |= masked << stream->head;
		fwrite(&stream->buffer, 8, 1, stream->file); //FIXME: No error checking
		stream->head = 0;
		stream->buffer = 0;
		bits -= fbits;
		value >>= fbits;
	}

	if (bits == 0)
		goto _bit_stream_write_skip_no_flush;

	uint64_t mask = ~0 >> (64-bits);
	uint64_t masked = value & mask;
	stream->buffer |= masked << (stream->head);
	stream->head += bits;

_bit_stream_write_skip_no_flush:
	return SUS_SUCCESS;
}
int bitstream_read(bitstream_t *stream, uint64_t *store, int bits)
{//FIXME: Does not prevent reading past end of file
	if (stream->write) return SUS_BITSTREAM_ACCESS;
	if (bits < 0 || bits > 64) return SUS_INVALID_ARG;

	uint64_t value = 0;
	int rbits = bits;

	if (bits >= 64 - stream->head) //Needs reading
	{
		int valid_bits = 64 - stream->head;
		int shift = 64 - valid_bits;
		value = shift < 64 ? (stream->buffer >> shift) : 0;
		rbits -= valid_bits;
		stream->head = 0;
		fread(&stream->buffer, 1, 8, stream->file); //FIXME: No error checking
	}

	if (rbits == 0)
		goto _bit_stream_read_skip_no_read;

	uint64_t mask = ~(uint64_t)0 >> (64-rbits);
	uint64_t masked = (stream->buffer >> stream->head) & mask;
	value |= masked << (bits - rbits);
	stream->head += rbits;

_bit_stream_read_skip_no_read:
	*store = value;
	return SUS_SUCCESS;
}
int bitstream_destroy(bitstream_t *stream)
{
	if (!stream->write) goto _bit_stream_destroy_skip_flush;

	if (stream->head) //Flush if needed
		fwrite(&stream->buffer, 1, DIV_CEIL(stream->head, 8), stream->file); //FIXME: No error checking
	fflush(stream->file);

_bit_stream_destroy_skip_flush:
	free(stream);
	return SUS_SUCCESS;
}
