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

/* find ::: ref {{{ */

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

size_t _so_find_nch(So_Ref ref, char c) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        if(ref.str[i] != c) return i;
    }
    return ref.len;
} /*}}}*/

size_t _so_find_ws(So_Ref ref) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        if(isspace(ref.str[i])) return i;
    }
    return ref.len;
} /*}}}*/

size_t _so_find_nws(So_Ref ref) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        if(!isspace(ref.str[i])) return i;
    }
    return ref.len;
} /*}}}*/

size_t _so_find_any(So_Ref ref, So_Ref any) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        char c = ref.str[i];
        if(memchr(any.str, c, any.len)) {
            return i;
        }
    }
    return ref.len;
} /*}}}*/

size_t _so_find_nany(So_Ref ref, So_Ref nany) { /*{{{*/
    for(size_t i = 0; i < ref.len; ++i) {
        char c = ref.str[i];
        if(!memchr(nany.str, c, nany.len)) {
            return i;
        }
    }
    return ref.len;
} /*}}}*/

size_t _so_find_sub(So_Ref ref, So_Ref sub, bool ignorecase) { /*{{{*/
    /* basic checks */
    if(!sub.len) return 0;
    if(sub.len > ref.len) return ref.len;
    size_t len = ref.len;
    /* check for substring */
    size_t i = 0, shift = 0, overlap = 0;
    while(ref.len >= sub.len) {
        overlap = _so_count_overlapx(ref, sub, ignorecase ? SO_CMP_CASE_INSENSITIVE : SO_CMP);
        if(overlap == sub.len) return i;
        i += overlap;
        so_ref_shift(&ref, overlap);
        shift = _so_find_ch(ref, sub.str[0]);
        /*if(!shift && ref.len) ++shift;//don't think I need this?*/
        i += shift;
        so_ref_shift(&ref, shift);
    }
    return len;
} /*}}}*/

/*}}}*/

/* find ::: regular {{{ */

size_t so_find_ch(So so, char c) { /*{{{*/
    return _so_find_ch(so_ref(so), c);
} /*}}}*/

size_t so_find_nch(So so, char c) { /*{{{*/
    return _so_find_nch(so_ref(so), c);
} /*}}}*/

size_t so_find_ws(So so) { /*{{{*/
    return _so_find_ws(so_ref(so));
} /*}}}*/

size_t so_find_nws(So so) { /*{{{*/
    return _so_find_nws(so_ref(so));
} /*}}}*/

size_t so_find_any(So so, So any) { /*{{{*/
    return _so_find_any(so_ref(so), so_ref(any));
} /*}}}*/

size_t so_find_nany(So so, So any) { /*{{{*/
    return _so_find_nany(so_ref(so), so_ref(any));
} /*}}}*/

size_t so_find_sub(So so, So sub, bool ignorecase) { /*{{{*/
    return _so_find_sub(so_ref(so), so_ref(sub), ignorecase ? SO_CMP_CASE_INSENSITIVE : SO_CMP);
} /*}}}*/

/*}}}*/

/* rfind ::: ref {{{ */

size_t _so_rfind_ch(So_Ref ref, char c) { /*{{{*/
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
} /*}}}*/

size_t _so_rfind_nch(So_Ref ref, char c) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        if(ref.str[i - 1] != c) return i;
    }
    return 0;
} /*}}}*/

size_t _so_rfind_ws(So_Ref ref) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        if(isspace(ref.str[i - 1])) return i - 1;
    }
    return ref.len;
} /*}}}*/

size_t _so_rfind_nws(So_Ref ref) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        if(!isspace(ref.str[i - 1])) return i;
    }
    return 0;
} /*}}}*/

size_t _so_rfind_any(So_Ref ref, So_Ref any) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        char c = ref.str[i - 1];
        if(memchr(any.str, c, any.len)) {
            return i - 1;
        }
    }
    return ref.len;
} /*}}}*/

size_t _so_rfind_nany(So_Ref ref, So_Ref nany) { /*{{{*/
    for(size_t i = ref.len; i > 0; --i) {
        char c = ref.str[i - 1];
        if(!memchr(nany.str, c, nany.len)) {
            return i;
        }
    }
    return 0;
} /*}}}*/

size_t _so_rfind_sub(So_Ref ref, So_Ref sub, bool ignorecase) {
    /* basic checks */
    if(!sub.len) return 0;
    if(sub.len > ref.len) return ref.len;
    So_Ref sweep = ref;
    size_t len = ref.len;
    sweep.len = sub.len;
    /* check for substring */
    size_t shift = 0, overlap = 0;
    while(ref.len >= sub.len) {
        sweep.str = ref.str + ref.len - sub.len;
        overlap = _so_count_overlapx(sweep, sub, ignorecase ? SO_CMP_CASE_INSENSITIVE : SO_CMP);
        if(overlap == sub.len) return ref.len - sweep.len;
        ref.len -= overlap;
        shift = _so_rfind_ch(ref, sub.str[0]);
        if(shift < ref.len) shift -= sub.len;
        ref.len -= shift;
    }
    return len;
}

/*}}}*/

/* rfind ::: regular {{{ */

size_t so_rfind_ch(So so, char c) { /*{{{*/
    return _so_rfind_ch(so_ref(so), c);
} /*}}}*/

size_t so_rfind_nch(So so, char c) { /*{{{*/
    return _so_rfind_nch(so_ref(so), c);
} /*}}}*/

size_t so_rfind_ws(So so) { /*{{{*/
    return _so_rfind_ws(so_ref(so));
} /*}}}*/

size_t so_rfind_nws(So so) { /*{{{*/
    return _so_rfind_nws(so_ref(so));
} /*}}}*/

size_t so_rfind_any(So so, So any) { /*{{{*/
    return _so_rfind_any(so_ref(so), so_ref(any));
} /*}}}*/

size_t so_rfind_nany(So so, So nany) { /*{{{*/
    return _so_rfind_nany(so_ref(so), so_ref(nany));
} /*}}}*/

size_t so_rfind_sub(So so, So sub, bool ignorecase) { /*{{{*/
    return _so_rfind_sub(so_ref(so), so_ref(sub), ignorecase ? SO_CMP_CASE_INSENSITIVE : SO_CMP);
} /*}}}*/

/*}}}*/

/* weird stuff {{{*/

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

/*}}}*/

