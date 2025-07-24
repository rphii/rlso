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
    So_Ref ref = so_ref(so);
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
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = 0; i < len; ++i) {
        if(s0[i] != c) return i;
    }
    return len;
} /*}}}*/

size_t so_find_ws(So so) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = 0; i < len; ++i) {
        if(isspace(s0[i])) return i;
    }
    return len;
} /*}}}*/

size_t so_find_nws(So so) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = 0; i < len; ++i) {
        if(!isspace(s0[i])) return i;
    }
    return len;
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
    So_Ref rso = so_ref(so);
    So_Ref rsub = so_ref(sub);
    /* basic checks */
    if(!rsub.len) return 0;
    if(rsub.len > rso.len) {
        return rso.len;
    }
    /* check for substring */
    size_t i = 0;
    while(rsub.len <= rso.len) {
        size_t overlap = so_count_overlap(so_ll(rso.str, rso.len), sub, attr & SO_CMP_CASE_INSENSITIVE);
        if(overlap == rsub.len) {
            return i;
        } else {
            i += overlap + 1;
            rso.str += overlap + 1;
            rso.len -= overlap + 1;
        }
    }
    return rso.len;
} /*}}}*/

size_t so_find_nsub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    assert(0);
} /*}}}*/

size_t so_rfind_ch(So so, char c) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
#if 1
    char *s = memrchr(s0, c, len);
    if(!s) return len;
    return s - s0;
#else
    for(size_t i = so_len(so); i > 0; --i) {
        if(so.so[i - 1] == c) return i - 1;
    }
    return len;
#endif
} /*}}}*/

size_t so_rfind_nch(So so, char c) { /*{{{*/
    size_t len = so_len(so);
    char *s0 = so_it0(so);
    for(size_t i = len; i > 0; --i) {
        if(s0[i - 1] != c) return i - 1;
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
    So_Ref ref = so_ref(so);
    for(size_t i = ref.len; i > 0; --i) {
        if(!isspace(ref.str[i - 1])) return i - 1;
    }
    return ref.len;
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
    /* basic checks */
    So_Ref rso = so_ref(so);
    So_Ref rsub = so_ref(sub);
    size_t n = rsub.len;
    size_t m = rso.len;
    if(!n) return 0;
    if(n > m) {
        return m;
    }
    const char *s = rsub.str;
    for(size_t i = m - n + 1; i > 0; --i) {
        const char *t = so_it(so, i - 1);
        if(!memcmp(s, t, n)) return i - 1;
    }
    return m;
} /*}}}*/

size_t so_rfind_nsub(So so, So sub, So_Cmp_Attr attr) { /*{{{*/
    assert(0);
} /*}}}*/

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

