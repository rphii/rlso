#define _GNU_SOURCE
#include "so.h"
#include "so-find.h"
#include "so-cmp.h"
#include "so-count.h"
#include "so-cmp-attr.h"
#include <assert.h>
#include <ctype.h>
#include <rl/colorprint.h>

#include <rl/err.h>

size_t so_find_ch(So so, char c) { /*{{{*/
    return _so_find_ch(so_ref(so), c);
} /*}}}*/

size_t _so_find_ch(So_Ref ref, char c) { /*{{{*/
#if 1
    char *s = memchr(ref.str, c, ref.len);
    if(!s) return ref.len;
    return s - ref.str;
#else
    for(size_t i = 0; i < len; ++i) {
        if(s0[i] == c) return i;
    }
    return len;
#endif
} /*}}}*/

size_t so_find_nch(So so, char c) { /*{{{*/
    return _so_find_nch(so_ref(so), c);
} /*}}}*/

size_t _so_find_nch(So_Ref ref, char c) {
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] != c) return i;
    }
    return ref.len;
}

size_t so_find_ws(So so) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = 0; i < len; ++i) {
        if(isspace(s0[i])) return i;
    }
    return len;
} /*}}}*/

size_t so_find_nws(So so) { /*{{{*/
    return _so_find_nws(so_ref(so));
} /*}}}*/

size_t _so_find_nws(So_Ref ref) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        if(!isspace(ref.str[i])) return i;
    }
    return ref.len;
} /*}}}*/

size_t so_find_any(So so, So any) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    size_t len2 = so_len(any);
    char *b0 = so_it0(any);
    for(size_t i = 0; i < len; ++i) {
        char c = s0[i];
        if(memchr(b0, c, len2)) {
            return i;
        }
    }
    return len;
} /*}}}*/

size_t so_find_nany(So so, So any) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    size_t len2 = so_len(any);
    char *b0 = so_it0(any);
    for(size_t i = 0; i < len; ++i) {
        char c = s0[i];
        if(!memchr(b0, c, len2)) {
            return i;
        }
    }
    return len;
} /*}}}*/

size_t so_find_sub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    return _so_find_sub(so_ref(so), sub, attr);
} /*}}}*/

size_t _so_find_sub(So_Ref ref, So sub, So_Cmp_Attr attr) { /*{{{*/
    So_Ref rsub = so_ref(sub);
    /* basic checks */
    if(!rsub.len) return 0;
    if(rsub.len > ref.len) {
        return ref.len;
    }
    /* check for substring */
    size_t i = 0;
    while(rsub.len <= ref.len) {
        size_t overlap = so_count_overlap(so_ll(ref.str, ref.len), sub, attr & SO_CMP_CASE_INSENSITIVE);
        if(overlap == rsub.len) {
            return i;
        } else {
            i += overlap + 1;
            ref.str += overlap + 1;
            ref.len -= overlap + 1;
        }
    }
    return ref.len;
} /*}}}*/

size_t so_find_nsub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    ABORT("implement");
} /*}}}*/

size_t _so_find_nsub(So_Ref, So sub, So_Cmp_Attr attr) {
    ABORT("implement");
}

size_t so_rfind_ch(So so, char c) { /*{{{*/
    return _so_rfind_ch(so_ref(so), c);
} /*}}}*/

size_t _so_rfind_ch(So_Ref ref, char c) {
#if 1
    char *s = memrchr(ref.str, c, ref.len);
    if(!s) return ref.len;
    return s - ref.str;
#else
    for(size_t i = ref.len; i > 0; --i) {
        if(ref.str[i - 1] == c) return i - 1;
    }
    return ref.len;
#endif
}

size_t so_rfind_nch(So so, char c) { /*{{{*/
    return _so_rfind_nch(so_ref(so), c);
} /*}}}*/

size_t _so_rfind_nch(So_Ref ref, char c) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        if(ref.str[i - 1] != c) return i;
    }
    return 0;
} /*}}}*/

size_t so_rfind_ws(So so) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = len; i > 0; --i) {
        if(isspace(s0[i - 1])) return i - 1;
    }
    return len;
} /*}}}*/

size_t so_rfind_nws(So so) { /*{{{*/
    return _so_rfind_nws(so_ref(so));
} /*}}}*/

size_t _so_rfind_nws(So_Ref ref) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        if(!isspace(ref.str[i - 1])) return i;
    }
    return 0;
} /*}}}*/

size_t so_rfind_any(So so, So any) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    size_t len2 = so_len(any);
    char *b0 = so_it0(any);
    for(size_t i = len; i > 0; --i) {
        char c = s0[i - 1];
        if(memchr(b0, c, len2)) {
            return i - 1;
        }
    }
    return len;
} /*}}}*/

size_t so_rfind_nany(So so, So any) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    size_t len2 = so_len(any);
    char *b0 = so_it0(any);
    for(size_t i = len; i > 0; --i) {
        char c = s0[i - 1];
        if(!memchr(b0, c, len2)) {
            return i - 1;
        }
    }
    return len;
} /*}}}*/

size_t so_rfind_sub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    return _so_rfind_sub(so_ref(so), sub, attr);
} /*}}}*/

size_t _so_rfind_sub(So_Ref str, So sub, So_Cmp_Attr attr) {
    /* basic checks */
    So_Ref rsub = so_ref(sub);
    size_t n = rsub.len;
    size_t m = str.len;
    if(!n) return 0;
    if(n > m) {
        return m;
    }
    const char *s = rsub.str;
    for(size_t i = m - n + 1; i > 0; --i) {
        const char *t = _so_it(str, i - 1);
        if(!memcmp(s, t, n)) return i - 1;
    }
    return m;
}

size_t so_rfind_nsub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    ABORT("implement");
} /*}}}*/

size_t _so_rfind_nsub(So_Ref ref, So sub, So_Cmp_Attr attr) {
    ABORT("implement");
}

#include <rl/err.h>
size_t so_find_f(So so, size_t *out_iE) { /*{{{*/
    size_t i0 = so_find_sub(so, so(FS_BEG), false);
    if(out_iE) {
        So s = so_i0(so, i0);
        size_t iE = so_find_ch(s, 'm');
        if(iE < so_len(s)) ++iE;
        *out_iE = i0 + iE;
    }
    return i0;
} /*}}}*/

size_t so_rfind_f0(So str, So *fmt) { /*{{{*/
    size_t i0 = so_rfind_sub(str, so(FS_BEG), false);
    So s = so_i0(str, i0);
    size_t iE = so_find_ch(s, 'm');
    if(iE < so_len(s)) ++iE;
    s = so_iE(s, iE);
    if(!so_cmpE(s, so("[0m"))) so_clear(&s);
    if(fmt) *fmt = s;
    return i0;
} /*}}}*/

size_t so_rfind_f(So so, size_t *out_iE) { /*{{{*/
    size_t i0 = so_rfind_sub(so, so(FS_BEG), false);
    if(out_iE) {
        So s = so_i0(so, i0);
        size_t iE = so_rfind_ch(s, 'm');
        if(iE < so_len(s)) ++iE;
        *out_iE = i0 + iE;
    }
    return i0;
} /*}}}*/

