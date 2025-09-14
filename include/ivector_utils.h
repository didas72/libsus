#ifndef SUS_IVECTOR_UTILS_H_
#define SUS_IVECTOR_UTILS_H_

#include "versioning.h"
#include "ivector.h"

static inline char ivector_get_char(ivector_t *vec, size_t index)
{ return *(char*)ivector_get(vec, index); }

static inline signed char ivector_get_schar(ivector_t *vec, size_t index)
{ return *(signed char*)ivector_get(vec, index); }
static inline short ivector_get_short(ivector_t *vec, size_t index)
{ return *(short*)ivector_get(vec, index); }
static inline int ivector_get_int(ivector_t *vec, size_t index)
{ return *(int*)ivector_get(vec, index); }
static inline long ivector_get_long(ivector_t *vec, size_t index)
{ return *(long*)ivector_get(vec, index); }

static inline unsigned char ivector_get_uchar(ivector_t *vec, size_t index)
{ return *(unsigned char*)ivector_get(vec, index); }
static inline unsigned short ivector_get_ushort(ivector_t *vec, size_t index)
{ return *(unsigned short*)ivector_get(vec, index); }
static inline unsigned int ivector_get_uint(ivector_t *vec, size_t index)
{ return *(unsigned int*)ivector_get(vec, index); }
static inline unsigned long ivector_get_ulong(ivector_t *vec, size_t index)
{ return *(unsigned long*)ivector_get(vec, index); }

static inline float ivector_get_float(ivector_t *vec, size_t index)
{ return *(float*)ivector_get(vec, index); }
static inline double ivector_get_double(ivector_t *vec, size_t index)
{ return *(double*)ivector_get(vec, index); }
static inline long double ivector_get_long_double(ivector_t *vec, size_t index)
{ return *(long double*)ivector_get(vec, index); }

static inline void *ivector_get_voidp(ivector_t *vec, size_t index)
{ return *(void**)ivector_get(vec, index); }

#ifdef SUS_IVECUTILS_USE_STDINT
#include <stdint.h>
static inline int8_t ivector_get_i8(ivector_t *vec, size_t index)
{ return *(int8_t*)ivector_get(vec, index); }
static inline int16_t ivector_get_i16(ivector_t *vec, size_t index)
{ return *(int16_t*)ivector_get(vec, index); }
static inline int32_t ivector_get_i32(ivector_t *vec, size_t index)
{ return *(int32_t*)ivector_get(vec, index); }
static inline int64_t ivector_get_i64(ivector_t *vec, size_t index)
{ return *(int64_t*)ivector_get(vec, index); }

static inline uint8_t ivector_get_u8(ivector_t *vec, size_t index)
{ return *(uint8_t*)ivector_get(vec, index); }
static inline uint16_t ivector_get_u16(ivector_t *vec, size_t index)
{ return *(uint16_t*)ivector_get(vec, index); }
static inline uint32_t ivector_get_u32(ivector_t *vec, size_t index)
{ return *(uint32_t*)ivector_get(vec, index); }
static inline uint64_t ivector_get_u64(ivector_t *vec, size_t index)
{ return *(uint64_t*)ivector_get(vec, index); }
#endif

#ifdef SUS_IVECUTILS_USE_STDDEF
#include <stddef.h>
static inline size_t ivector_get_sizet(ivector_t *vec, size_t index)
{ return *(size_t*)ivector_get(vec, index); }
static inline ptrdiff_t ivector_get_ptrdifft(ivector_t *vec, size_t index)
{ return *(ptrdiff_t*)ivector_get(vec, index); }
#endif

#ifdef SUS_IVECUTILS_USE_BOOL

#if (__STDC_VERSION__ < 202000)
#include <stdbool.h>
#endif

static inline bool ivector_get_bool(ivector_t *vec, size_t index)
{ return *(bool*)ivector_get(vec, index); }
#endif

#endif
