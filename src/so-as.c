#include "so-core.h"
#include "so-cmp.h"
#include "so-as.h"
#include <rl/err.h>
#include <stdint.h>
#include <limits.h>

#define SO_AS_SIZE_BASE_MAX     36

static int static_so_as_unbase_char(char c) {
    if(c >= '0' && c <= '9') return c - '0';
    if(c >= 'a' && c <= 'z') return c - 'a' + 10;
    if(c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

void so_as_cstr(So so, char *buf, size_t cap) {
    ASSERT_ARG(buf);
    So ref = so;
    if(ref.len && cap) {
        size_t less = ref.len < cap - 1 ? ref.len : cap - 1;
        memcpy(buf, ref.str, less);
    }
    if(cap) {
        buf[ref.len] = 0;
    }
}

void so_as_get_base(So *ref, int *base) {
    int base_use = *base ? *base : 10;
    if(ref->len >= 2 && ref->str[0] == '0') {
        so_shift(ref, 1);
        if(ref->str[0] == 'x' || ref->str[0] == 'X') {
            so_shift(ref, 1);
            base_use = *base ? *base : 16;
        } else if(ref->str[0] == 'b' || ref->str[0] == 'b') {
            so_shift(ref, 1);
            base_use = *base ? *base : 2;
        } else {
            base_use = *base ? *base : 8;
        }
    }
    *base = base_use;
}

void so_as_get_sign(So *ref, bool *sign) {
    if(ref->len >= 1) {
        if(ref->str[0] == '-') {
            *sign = true;
            so_shift(ref, 1);
        } else if(ref->str[0] == '+') {
            so_shift(ref, 1);
        }
    } else {
        *sign = false;
    }
}

#define SO_AS_WITH_BASE(T, ref, base_use, sign, out, bound) \
    do { \
        if(!ref.len) return -1; \
        if(base_use > SO_AS_SIZE_BASE_MAX) return -1; \
        T result = 0; \
        for(size_t i = 0; i < ref.len; ++i) { \
            int val = static_so_as_unbase_char(ref.str[i]); \
            if(val < 0 || val >= base_use) { \
                return -1; \
            } \
            T next = result * base_use + val; \
            if(next < result) { \
                *out = bound; \
                return -1; \
            } \
            result = next; \
        } \
        *out = sign ? -result : result; \
        return 0; \
    } while(0)

ErrDecl so_as_bool_strict(So so, bool *out) {
    if(!so_cmp(so, so("true"))) {
        *out = true;
    } else if(!so_cmp(so, so("false"))) {
        *out = false;
    } else {
        return -1;
    }
    return 0;
}

ErrDecl so_as_char(So so, char *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? CHAR_MIN : CHAR_MAX);
}

ErrDecl so_as_short(So so, short *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? SHRT_MIN : SHRT_MAX);
}

ErrDecl so_as_int(So so, int *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? INT_MIN : INT_MAX);
}

ErrDecl so_as_long(So so, long *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? LONG_MIN : LONG_MAX);
}

ErrDecl so_as_longlong(So so, long long *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? LLONG_MIN : LLONG_MAX);
}


ErrDecl so_as_ssize(So so, ssize_t *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ssize_t, so, base, sign, out, sign ? SSIZE_MIN : SSIZE_MAX);
}


ErrDecl so_as_uchar(So so, unsigned char *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(unsigned char, so, base, false, out, UCHAR_MAX);
}

ErrDecl so_as_ushort(So so, ushort *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ushort, so, base, false, out, USHRT_MAX);
}

ErrDecl so_as_uint(So so, uint *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ulong, so, base, false, out, UINT_MAX);
}

ErrDecl so_as_ulong(So so, ulong *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(ulong, so, base, false, out, ULONG_MAX);
}

ErrDecl so_as_ulonglong(So so, unsigned long long *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(unsigned long long, so, base, false, out, ULLONG_MAX);
}

ErrDecl so_as_size(So so, size_t *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(size_t, so, base, false, out, SIZE_MAX);
}


ErrDecl so_as_i8(So so, int8_t *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(int8_t, so, base, sign, out, sign ? INT8_MIN : INT8_MAX);
}

ErrDecl so_as_i16(So so, int16_t *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(int16_t, so, base, sign, out, sign ? INT16_MIN : INT16_MAX);
}

ErrDecl so_as_i32(So so, int32_t *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(int32_t, so, base, sign, out, sign ? INT32_MIN : INT32_MAX);
}

ErrDecl so_as_i64(So so, int64_t *out, int base) {
    bool sign = false;
    so_as_get_sign(&so, &sign);
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(int64_t, so, base, sign, out, sign ? INT64_MIN : INT64_MAX);
}


ErrDecl so_as_u8(So so, uint8_t *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(uint8_t, so, base, false, out, UINT8_MAX);
}

ErrDecl so_as_u16(So so, uint16_t *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(uint16_t, so, base, false, out, UINT16_MAX);
}

ErrDecl so_as_u32(So so, uint32_t *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(uint32_t, so, base, false, out, UINT32_MAX);
}

ErrDecl so_as_u64(So so, uint64_t *out, int base) {
    so_as_get_base(&so, &base);
    SO_AS_WITH_BASE(uint64_t, so, base, false, out, UINT64_MAX);
}



