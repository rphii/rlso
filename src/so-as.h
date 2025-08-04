#ifndef SO_AS_H

#include <stdint.h>
#include <stddef.h>
#include <rl/err.h>

typedef struct So So;

void so_as_cstr(So so, char *cstr, size_t cap);

ErrDecl so_as_float(So so, float *out);
ErrDecl so_as_double(So so, double *out);
ErrDecl so_as_longdouble(So so, long double *out);

ErrDecl so_as_bool(So so, bool *out);
ErrDecl so_as_yes_or_no(So so, bool *out);

ErrDecl so_as_char(So so, char *out, int base);
ErrDecl so_as_uchar(So so, unsigned char *out, int base);
ErrDecl so_as_short(So so, short *out, int base);
ErrDecl so_as_ushort(So so, ushort *out, int base);
ErrDecl so_as_int(So so, int *out, int base);
ErrDecl so_as_uint(So so, uint *out, int base);
ErrDecl so_as_long(So so, long *out, int base);
ErrDecl so_as_ulong(So so, ulong *out, int base);
ErrDecl so_as_size(So so, size_t *out, int base);
ErrDecl so_as_ssize(So so, ssize_t *out, int base);
ErrDecl so_as_longlong(So so, long long *out, int base);
ErrDecl so_as_ulonglong(So so, unsigned long long *out, int base);

ErrDecl so_as_i8(So so, int8_t *out, int base);
ErrDecl so_as_i16(So so, int16_t *out, int base);
ErrDecl so_as_i32(So so, int32_t *out, int base);
ErrDecl so_as_i64(So so, int64_t *out, int base);

ErrDecl so_as_u8(So so, uint8_t *out, int base);
ErrDecl so_as_u16(So so, uint16_t *out, int base);
ErrDecl so_as_u32(So so, uint32_t *out, int base);
ErrDecl so_as_u64(So so, uint64_t *out, int base);

#define SO_AS_H
#endif

