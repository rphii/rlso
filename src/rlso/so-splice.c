#include "so-core.h"
#include "so-find.h"
#include "so-split.h"
#include "so-splice.h"
#include <rlc.h>
#include <stdlib.h>

inline size_t so_splice(So to_splice, So *prev, char sep) {
    ASSERT_ARG(prev);
    size_t len = so_len(to_splice);
    So result = so_ll(to_splice.str, len);
    if(prev && prev->str) {
        size_t from = prev->str - to_splice.str + so_len(*prev);
        So search = so_i0(to_splice, from);
        size_t offset = so_find_ch(search, sep) + from;
        result.str += offset;
        result.len -= offset;
        if(result.str - to_splice.str < so_len(to_splice)) {
            ++result.str;
            --result.len;
        }
    }
    result.len = so_find_ch(result, sep);
    *prev = result;
    return result.str - to_splice.str - len;
} /*}}}*/


