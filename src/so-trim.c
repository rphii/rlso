#include "so-core.h"
#include "so-trim.h"
#include "so-find.h"

So so_trim(So ref) {
    ref = so_triml(ref); /* first trim left */
    So result = so_trimr(ref);
    //if(ref2.len < ref.len) ++ref.len;
    return result;
}

So so_triml(So ref) {
    So result = so_i0(ref, so_find_nws(ref));
    return result;
}

So so_trimr(So ref) {
    size_t i = so_rfind_nws(ref);
    //if(i >= ref.len) return so_rev(ref);
    if(i >= ref.len) return ref;
    So result = so_iE(ref, i);
    return result;
}


