#include "so.h"
#include "so-find.h"
#include "so-split.h"
#include "so-splice.h"
#include <rl/err.h>
#include <stdlib.h>

size_t _so_splice(So_Ref to_splice, So *prev, char sep) {
    ASSERT_ARG(prev);
    So_Ref pref = _so_ref(prev);
    So result = {0};
    if(prev && !so_is_zero(*prev)) {
        size_t from = 1 + pref.len + pref.str - to_splice.str; /* +1 to skip separator */
        result = so_split_ch(_so_i0(to_splice, from), sep, 0);
    } else {
        result = _so_split_ch(to_splice, sep, 0);
    }
    *prev = result;
    return result.ref.str - to_splice.str - to_splice.len;
} /*}}}*/


