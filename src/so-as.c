#include "so.h"
#include "so-as.h"
#include <rl/err.h>
#include <stdint.h>

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

ErrDecl _so_as_size(So ref, size_t *out, int base) {
    if(!ref.len) return -1;
    if(base > SO_AS_SIZE_BASE_MAX) return -1;
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        int val = static_so_as_unbase_char(ref.str[i]);
        if(val < 0 || val >= base) {
            return -1;
        }
        size_t next = result * base + val;
        if(next < result) {
            *out = SIZE_MAX;
            return -1;
        }
        result = next;
    }
    *out = result;
    return 0;
}

ErrDecl so_as_size(So so, size_t *out, int base) {
    So ref = so;
    size_t base_use = base ? base : 10;
    if(ref.len >= 2 && ref.str[0] == '0') {
        so_shift(&ref, 1);
        if(ref.str[0] == 'x' || ref.str[0] == 'X') {
            so_shift(&ref, 1);
            base_use = base ? base : 16;
        } else if(ref.str[0] == 'b' || ref.str[0] == 'b') {
            so_shift(&ref, 1);
            base_use = base ? base : 2;
        } else {
            base_use = base ? base : 8;
        }
    }
    int result = _so_as_size(ref, out, base_use);
    return result;
}

