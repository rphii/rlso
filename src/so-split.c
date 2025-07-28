#include "so.h"
#include "so-find.h"
#include "so-split.h"

So _so_split(So_Ref ref, size_t i, So *right) {
    if(right) *right = _so_i0(ref, i);
    So left = _so_iE(ref, i);
    return left;
}

So _so_split_ext(So_Ref ref, size_t i, size_t n, So *right) {
    if(right) {
        if(i + n <= ref.len) *right = _so_i0(ref, i + n);
        else *right = _so_i0(ref, i);
    }
    So left = _so_iE(ref, i);
    return left;
}


So _so_split_ch(So_Ref ref, char c, So *right) {
    size_t i = _so_find_ch(ref, c);
    return _so_split_ext(ref, i, 1, right);
}

So _so_split_nch(So_Ref ref, char c, So *right) {
    size_t i = _so_find_nch(ref, c);
    return _so_split_ext(ref, i, 1, right);
}

So _so_split_sub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = _so_find_sub(ref, sub, attr);
    return _so_split_ext(ref, i, so_len(sub), right);
}

So _so_split_nsub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = _so_find_nsub(ref, sub, attr);
    return _so_split_ext(ref, i, so_len(sub), right);
}


So _so_rsplit_ch(So_Ref ref, char c, So *right) {
    size_t i = _so_rfind_ch(ref, c);
    return _so_split_ext(ref, i, 1, right);
}

So _so_rsplit_nch(So_Ref ref, char c, So *right) {
    size_t i = _so_rfind_nch(ref, c);
    return _so_split_ext(ref, i, 1, right);
}

So _so_rsplit_sub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = _so_rfind_sub(ref, sub, attr);
    return _so_split_ext(ref, i, so_len(sub), right);
}

So _so_rsplit_nsub(So_Ref ref, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = _so_rfind_nsub(ref, sub, attr);
    return _so_split_ext(ref, i, so_len(sub), right);
}


