#include <rlc/platform-detect.h>
#include <rlc/err.h>

#include "so-core.h"
#include "so-find.h"
#include "so-path.h"
#include "so-split.h"
#include "so-print.h"
#include "so-cmp.h"

inline void so_path_join(So *out, So a, So b) {
    So tmp = so_clone(b);
    bool non_root = (so_cmp(a, so(PLATFORM_S_SUBDIR)));
    so_clear(out);
    so_extend(out, so_ensure_dir(a));
    if(non_root) so_push(out, PLATFORM_CH_SUBDIR);
    so_extend(out, so_ensure_dir(tmp));
    so_free(&tmp);
    *out = so_ensure_dir(*out);
}


inline const So so_get_ext(So ref) { /*{{{*/
    /* also handles: file.dir/filename -> / is after . */
    So result = SO;
    size_t i = so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    size_t j = so_rfind_ch(ref, '.');
    if(j > i || i >= so_len(ref)) {
        result = so_i0(ref, j);
    }
    return result;
} /*}}}*/

inline const So so_get_noext(So ref) { /*{{{*/
#if 1
    /* also handles: file.dir/filename -> / is after . */
    size_t i = so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    size_t j = so_rfind_ch(ref, '.');
    size_t sp = (j < i || j == ref.len) ? ref.len : j;
    So result = so_iE(ref, sp);
#else
    So ref = so_ref(str);
    So result = { .ref = ref };
    if(ref.len) {
        size_t i = so_rfind_ch(result, '.');
        if(i < ref.len) {
            /* in case we have something like: file.dir/filename -> / is after . */
            size_t j = so_rfind_ch(result, PLATFORM_CH_SUBDIR);
            if((j < ref.len && j < i) || (j == ref.len)) {
                result.ref.len = i;
            }
        }
    }
#endif
    return result;
} /*}}}*/

inline const So so_get_dir(So ref) { /*{{{*/
#if 1
    size_t i = so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    So result = i < ref.len ? so_iE(ref, i) : SO;
#else
    So ref = so_ref(str);
    So result = { .ref = ref };
    if(ref.len) {
        size_t i0 = so_rfind_ch(result, '/');
        if(i0 < ref.len && PLATFORM_CH_SUBDIR != '/') {
            i0 = so_rfind_ch(result, PLATFORM_CH_SUBDIR);
        }
        /*if(i0 < len) ++i0;*/
        else if(i0 >= ref.len) i0 = 0;
        result.ref.len = i0;
    }
#endif
    return result;
} /*}}}*/

inline const So so_get_nodir(So ref) { /*{{{*/
#if 1
    size_t i = so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    So result = i < ref.len ? so_i0(ref, i + 1) : ref;
#else
    So ref = so_ref(str);
    So result = { .ref = ref };
    if(ref.len) {
        size_t i0 = so_rfind_ch(result, '/');
        if(i0 < ref.len && PLATFORM_CH_SUBDIR != '/') {
            i0 = so_rfind_ch(result, PLATFORM_CH_SUBDIR);
        }
        if(i0 < ref.len) ++i0;
        else if(i0 >= ref.len) i0 = 0;
        result.ref.str += i0;
        result.ref.len -= i0;
    }
#endif
    return result;
} /*}}}*/

inline const So so_get_basename(So ref) { /*{{{*/
#if 1
    So result = SO;
    so_rsplit_ch(ref, PLATFORM_CH_SUBDIR, &result);
    if(!so_len(result)) result = ref;
    result = so_rsplit_ch(result, '.', 0);
#else
    So ref = so_ref(str);
    So result = { .ref = ref };
    if(ref.len) {
        size_t iE = so_rfind_ch(result, '.');
        size_t i0 = so_rfind_ch(result, '/');
        if(i0 < ref.len && PLATFORM_CH_SUBDIR != '/') {
            i0 = so_rfind_ch(result, PLATFORM_CH_SUBDIR);
        }
        if(i0 < ref.len) ++i0;
        if(iE < i0) iE = ref.len;
        else if(i0 >= ref.len) i0 = 0;
        result.ref.str += i0;
        result.ref.len = (iE - i0);
        /*TRYC(so_fmt(basename, "%.*s", (int)(iE - i0), so_iter_at(str, i0)));*/
    }
#endif
    return result;
} /*}}}*/


inline const So so_ensure_dir(So str) { /*{{{*/
    // !!! str = so_trim(str);
    size_t len = so_len(str);
    So result = so_ll(str.str, len);
    if(len > 1) {
        size_t nch = so_rfind_nch(str, PLATFORM_CH_SUBDIR);
        if(!nch && len) ++nch;
        else if(nch < len && so_at(str, nch) != PLATFORM_CH_SUBDIR) ++nch;
        result.len = nch;
        //if(so_at(result, so_len_raw(result) - 1) == PLATFORM_CH_SUBDIR) {
        //    --result.len;
        //}
    }
    return result;
} /*}}}*/

