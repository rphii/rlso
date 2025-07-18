#include "so.h"
#include "so-find.h"
#include "so-splice.h"
#include <rphii/err.h>
#include <stdlib.h>

size_t so_splice(So to_splice, So *prev, char sep) { /*{{{*/
    ASSERT_ARG(prev);
    So_Ref ref = so_ref(to_splice);
    So_Ref pref = _so_ref(prev);
    So result = so_ll(ref.str, ref.len);
    if(prev && prev->ref.str) {
        size_t from = prev->ref.str - to_splice.ref.str + pref.len;
        So search = so_i0(to_splice, from);
        size_t offset = so_find_ch(search, sep) + from;
        result.ref.str += offset;
        result.ref.len -= offset;
        if(result.ref.str - ref.str < ref.len) {
            ++result.ref.str;
            --result.ref.len;
        }
    }
    result.ref.len = so_find_ch(result, sep);
    *prev = result;
    return result.ref.str - to_splice.ref.str - ref.len;
} /*}}}*/


