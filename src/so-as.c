#include "so.h"
#include "so-as.h"
#include <stdlib.h>
#include <rphii/err.h>

void so_as_cstr(So so, char *buf, size_t cap) {
    ASSERT_ARG(buf);
    So_Ref ref = so_ref(so);
    if(ref.len && cap) {
        size_t less = ref.len < cap - 1 ? ref.len : cap - 1;
        memcpy(buf, ref.str, less);
    }
    if(cap) {
        buf[ref.len] = 0;
    }
}

ErrDecl so_as_size(So so, size_t *out, int base) {
    So_Ref ref = so_ref(so);
    if(!ref.len) return -1;
    char *endptr;
    char temp[32] = {0};
    so_as_cstr(so, temp, 32);
    size_t result = strtoull(temp, &endptr, base);
    if(endptr - temp != ref.len) return -1;
    if(out) *out = result;
    return 0;
}

