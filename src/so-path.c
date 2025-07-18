#include <rphii/platform-detect.h>

#include "so.h"
#include "so-find.h"
#include "so-path.h"

const So so_get_ext(So str) { /*{{{*/
    //size_t len = so_len_raw(str);
    //So result = so_ll(str.str, len);
    So_Ref ref = so_ref(str);
    So result = { .ref = ref };
    if(ref.len) {
        size_t i = so_rfind_ch(result, '.');
        if(i < ref.len) {
            /* in case we have something like: file.dir/filename -> / is after . */
            size_t j = so_rfind_ch(result, PLATFORM_CH_SUBDIR);
            if((j < ref.len && j < i) || (j == ref.len)) {
                result.ref.str += i;
                result.ref.len = ref.len - i;
            }
        }
    }
    return result;
} /*}}}*/

const So so_get_noext(So str) { /*{{{*/
    So_Ref ref = so_ref(str);
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
    return result;
} /*}}}*/

const So so_get_dir(So str) { /*{{{*/
    So_Ref ref = so_ref(str);
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
    return result;
} /*}}}*/

const So so_get_nodir(So str) { /*{{{*/
    So_Ref ref = so_ref(str);
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
    return result;
} /*}}}*/

const So so_get_basename(So str) { /*{{{*/
    So_Ref ref = so_ref(str);
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
    return result;
} /*}}}*/

