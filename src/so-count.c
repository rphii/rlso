#include "so.h"
#include "so-count.h"
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

size_t so_count_overlap(So a, So b, bool ignorecase) {
    return _so_count_overlap(so_ref(a), so_ref(b), ignorecase);
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

size_t _so_count_overlap(So_Ref ra, So_Ref rb, bool ignorecase) { /*{{{*/
    size_t overlap = 0;
    size_t len = ra.len > rb.len ? rb.len : ra.len;
    if(!ignorecase) {
        for(size_t i = 0; i < len; ++i) {
            char ca = ra.str[i];
            char cb = rb.str[i];
            if(ca == cb) ++overlap;
            else break;
        }
    } else {
        for(size_t i = 0; i < len; ++i) {
            int ca = tolower(ra.str[i]);
            int cb = tolower(rb.str[i]);
            if(ca == cb) ++overlap;
            else break;
        }
    }
    return overlap;
} /*}}}*/

