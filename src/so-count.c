#include "so-core.h"
#include "so-count.h"
#include "so-cmp.h"
#include <ctype.h>

size_t so_count_ch(So ref, char c) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] == c) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_nch(So ref, char c) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] != c) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_any(So ref, So any) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(memchr(any.str, ref.str[i], any.len)) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_nany(So ref, So nany) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(!memchr(nany.str, ref.str[i], nany.len)) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_overlapx(So ra, So rb, bool ignorecase) { /*{{{*/
    size_t overlap = 0;
    size_t len = ra.len > rb.len ? rb.len : ra.len;
    for(overlap = 0; overlap < len; ++overlap) {
        char ca = ra.str[overlap];
        char cb = rb.str[overlap];
        if(ignorecase) {
            ca = tolower(ca);
            cb = tolower(cb);
        }
        if(ca != cb) break;
    }
    return overlap;
} /*}}}*/

