#include "so.h"
#include "so-as.h"
#include <stdlib.h>

void so_as_cstr(So so, char *cstr, size_t cap) {
    So_Ref ref = so_ref(so);
    if(ref.len >= cap) exit(1);
    memcpy(cstr, ref.str, ref.len);
    cstr[ref.len] = 0;
}

