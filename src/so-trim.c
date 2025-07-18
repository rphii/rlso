#include "so.h"
#include "so-trim.h"
#include "so-find.h"

So so_trim(So so) {
    So result = so_triml(so_trimr(so));
    return result;
}

So so_triml(So so) {
    So result = so_i0(so, so_find_nws(so));
    return result;
}

So so_trimr(So so) {
    size_t len = so_len(so);
    size_t i = so_rfind_nws(so);
    if(i >= len) return so;
    So result = so_iE(so, i + 1);
    return result;
}


