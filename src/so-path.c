#include <rl/platform-detect.h>

#include "so.h"
#include "so-find.h"
#include "so-path.h"
#include "so-split.h"
#include "so-print.h"
#include<rl/err.h>

void so_path_join(So *out, So a, So b) {
    So tmp = so_clone(b);
    so_clear(out);
    so_extend(out, a);
    so_push(out, PLATFORM_CH_SUBDIR);
    so_extend(out, tmp);
    so_free(&tmp);
}


const So _so_get_ext(So_Ref ref) { /*{{{*/
    /* also handles: file.dir/filename -> / is after . */
    So result = SO;
    size_t i = _so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    size_t j = _so_rfind_ch(ref, '.');
    if(j > i) {
        result = _so_i0(ref, j);
    }
    return result;
} /*}}}*/

const So _so_get_noext(So_Ref ref) { /*{{{*/
#if 1
    /* also handles: file.dir/filename -> / is after . */
    size_t i = _so_rfind_ch(ref, PLATFORM_CH_SUBDIR);
    size_t j = _so_rfind_ch(ref, '.');
    size_t sp = (j < i || j == ref.len) ? ref.len : j;
    So result = _so_iE(ref, sp);
#else
    So_Ref ref = _so_ref(str);
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

const So _so_get_dir(So_Ref ref) { /*{{{*/
#if 1
    So result = _so_rsplit_ch(ref, PLATFORM_CH_SUBDIR, 0);
#else
    So_Ref ref = _so_ref(str);
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

const So _so_get_nodir(So_Ref ref) { /*{{{*/
#if 1
    So result = SO;
    _so_rsplit_ch(ref, PLATFORM_CH_SUBDIR, &result);
#else
    So_Ref ref = _so_ref(str);
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

const So _so_get_basename(So_Ref ref) { /*{{{*/
#if 1
    So result = SO;
    _so_rsplit_ch(ref, PLATFORM_CH_SUBDIR, &result);
    if(!so_len(result)) result = so_rev(ref);
    result = so_rsplit_ch(result, '.', 0);
#else
    So_Ref ref = _so_ref(str);
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

