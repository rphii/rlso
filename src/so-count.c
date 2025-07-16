#include "so.h"
#include "so-count.h"
#include <ctype.h>

size_t so_count_ch(So str, char c) { /*{{{*/
    size_t result = 0;
    So_Ref ref = so_ref(str);
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] == c) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_nch(So str, char c) { /*{{{*/
    size_t result = 0;
    So_Ref ref = so_ref(str);
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] != c) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_any(So str, So any) { /*{{{*/
    size_t result = 0;
    So_Ref ref = so_ref(str);
    So_Ref ref2 = so_ref(any);
    for(size_t i = 0; i < ref.len; ++i) {
        if(memchr(ref2.str, ref.str[i], ref2.len)) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_nany(So str, So any) { /*{{{*/
    size_t result = 0;
    So_Ref ref = so_ref(str);
    So_Ref ref2 = so_ref(any);
    for(size_t i = 0; i < ref.len; ++i) {
        if(!memchr(ref2.str, ref.str[i], ref2.len)) ++result;
    }
    return result;
} /*}}}*/

size_t so_count_overlap(So a, So b, bool ignorecase) { /*{{{*/
    size_t overlap = 0;
    So_Ref ra = so_ref(a);
    So_Ref rb = so_ref(b);
    size_t len = ra.len > rb.len ? ra.len  : rb.len;
    if(!ignorecase) {
        for(size_t i = 0; i < len; ++i) {
            char ca = ra.str[i];
            char cb = ra.str[i];
            if(ca == cb) ++overlap;
            else break;
        }
    } else {
        for(size_t i = 0; i < len; ++i) {
            int ca = tolower(ra.str[i]);
            int cb = tolower(ra.str[i]);
            if(ca == cb) ++overlap;
            else break;
        }
    }
    return overlap;
} /*}}}*/

