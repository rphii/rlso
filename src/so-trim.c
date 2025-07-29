#include "so.h"
#include "so-trim.h"
#include "so-find.h"

So _so_trim(So_Ref ref) {
    So result = so_triml(_so_trimr(ref));
    return result;
}

So _so_triml(So_Ref ref) {
    So result = _so_i0(ref, _so_find_nws(ref));
    return result;
}

So _so_trimr(So_Ref ref) {
    size_t i = _so_rfind_nws(ref);
    if(i >= ref.len) return so_rev(ref);
    So result = _so_iE(ref, i + 1);
    return result;
}


