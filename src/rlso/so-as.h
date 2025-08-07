#ifndef SO_AS_H

#include <stdint.h>
#include <stddef.h>
#include <rlc.h>

typedef struct So So;

void so_as_cstr(So so, char *cstr, size_t cap);

#define ERR_so_as_color(...) "failed parsing color"
ErrDecl so_as_color(So so, Color *out);

#define ERR_so_as_float(...) "failed parsing float"
ErrDecl so_as_float(So so, float *out);
#define ERR_so_as_double(...) "failed parsing double"
ErrDecl so_as_double(So so, double *out);
#define ERR_so_as_longdouble(...) "failed parsing long double"
ErrDecl so_as_longdouble(So so, long double *out);

#define ERR_so_as_bool_strict(...) "failed parsing bool (strict)"
ErrDecl so_as_bool_strict(So so, bool *out);
#define ERR_so_as_yes_or_no(...) "failed parsing yes-or-no"
ErrDecl so_as_yes_or_no(So so, bool *out);

#define ERR_so_as_char(...) "failed parsing char"
ErrDecl so_as_char(So so, char *out, int base);
#define ERR_so_as_short(...) "failed parsing short"
ErrDecl so_as_short(So so, short *out, int base);
#define ERR_so_as_int(...) "failed parsing int"
ErrDecl so_as_int(So so, int *out, int base);
#define ERR_so_as_long(...) "failed parsing long"
ErrDecl so_as_long(So so, long *out, int base);
#define ERR_so_as_longlong(...) "failed parsing long long"
ErrDecl so_as_longlong(So so, long long *out, int base);
#define ERR_so_as_ssize(...) "failed parsing ssize"
ErrDecl so_as_ssize(So so, ssize_t *out, int base);

#define ERR_so_as_uchar(...) "failed parsing unsigned char"
ErrDecl so_as_uchar(So so, unsigned char *out, int base);
#define ERR_so_as_ushort(...) "failed parsing unsigned short"
ErrDecl so_as_ushort(So so, ushort *out, int base);
#define ERR_so_as_uint(...) "failed parsing unsigned int"
ErrDecl so_as_uint(So so, uint *out, int base);
#define ERR_so_as_ulong(...) "failed parsing unsigned long"
ErrDecl so_as_ulong(So so, ulong *out, int base);
#define ERR_so_as_ulonglong(...) "failed parsing unsigned long long"
ErrDecl so_as_ulonglong(So so, unsigned long long *out, int base);
#define ERR_so_as_size(...) "failed parsing size"
ErrDecl so_as_size(So so, size_t *out, int base);

#define ERR_so_as_i8(...) "failed parsing i8"
ErrDecl so_as_i8(So so, int8_t *out, int base);
#define ERR_so_as_i16(...) "failed parsing i16"
ErrDecl so_as_i16(So so, int16_t *out, int base);
#define ERR_so_as_i32(...) "failed parsing i32"
ErrDecl so_as_i32(So so, int32_t *out, int base);
#define ERR_so_as_i64(...) "failed parsing i64"
ErrDecl so_as_i64(So so, int64_t *out, int base);

#define ERR_so_as_u8(...) "failed parsing u8"
ErrDecl so_as_u8(So so, uint8_t *out, int base);
#define ERR_so_as_u16(...) "failed parsing u16"
ErrDecl so_as_u16(So so, uint16_t *out, int base);
#define ERR_so_as_u32(...) "failed parsing u32"
ErrDecl so_as_u32(So so, uint32_t *out, int base);
#define ERR_so_as_u64(...) "failed parsing u64"
ErrDecl so_as_u64(So so, uint64_t *out, int base);

#define SO_AS_H
#endif

