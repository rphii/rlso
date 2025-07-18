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

