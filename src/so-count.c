#include "so.h"
#include "so-count.h"
#include "so-cmp.h"
#include <ctype.h>

size_t so_count_ch(So str, char c) {
    return _so_count_ch(so_ref(str), c);
}

size_t so_count_nch(So str, char c) {
    return _so_count_nch(so_ref(str), c);
}

size_t so_count_any(So str, So any) {
    return _so_count_any(so_ref(str), so_ref(any));
}

size_t so_count_nany(So str, So nany) {
    return _so_count_nany(so_ref(str), so_ref(nany));
}

size_t so_count_overlapx(So a, So b, So_Cmp_Attr attr) {
    return _so_count_overlapx(so_ref(a), so_ref(b), attr);
}


size_t _so_count_ch(So_Ref ref, char c) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] == c) ++result;
    }
    return result;
} /*}}}*/

size_t _so_count_nch(So_Ref ref, char c) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] != c) ++result;
    }
    return result;
} /*}}}*/

size_t _so_count_any(So_Ref ref, So_Ref any) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(memchr(any.str, ref.str[i], any.len)) ++result;
    }
    return result;
} /*}}}*/

size_t _so_count_nany(So_Ref ref, So_Ref nany) { /*{{{*/
    size_t result = 0;
    for(size_t i = 0; i < ref.len; ++i) {
        if(!memchr(nany.str, ref.str[i], nany.len)) ++result;
    }
    return result;
} /*}}}*/

size_t _so_count_overlapx(So_Ref ra, So_Ref rb, So_Cmp_Attr attr) { /*{{{*/
    size_t overlap = 0;
    size_t len = ra.len > rb.len ? rb.len : ra.len;
    ra.len = 1;
    rb.len = 1;
    for(overlap = 0; overlap < len; ++overlap) {
        if(_so_cmp(ra, rb)) break;
        ++ra.str;
        ++rb.str;
    }
    return overlap;
} /*}}}*/

