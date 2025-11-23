#include "so-core.h"
#include "so-find.h"
#include "so-split.h"

inline So so_split(So ref, size_t i, So *right) {
    if(right) *right = so_i0(ref, i);
    So left = so_iE(ref, i);
    return left;
}

inline So so_split_ext(So ref, size_t i, size_t n, So *right) {
    if(right) {
        if(i + n <= ref.len) *right = so_i0(ref, i + n);
        else *right = so_i0(ref, i);
    }
    So left = so_iE(ref, i);
    return left;
}

inline So so_split_ch(So ref, char c, So *right) {
    size_t i = so_find_ch(ref, c);
    return so_split_ext(ref, i, 1, right);
}

inline So so_split_nch(So ref, char c, So *right) {
    size_t i = so_find_nch(ref, c);
    return so_split_ext(ref, i, 0, right);
}

inline So so_split_sub(So ref, So sub, So *right, bool ignorecase) {
    size_t i = so_find_sub(ref, sub, ignorecase);
    return so_split_ext(ref, i, sub.len, right);
}


inline So so_rsplit_ch(So ref, char c, So *right) {
    size_t i = so_rfind_ch(ref, c);
    return so_split_ext(ref, i, 1, right);
}

inline So so_rsplit_nch(So ref, char c, So *right) {
    size_t i = so_rfind_nch(ref, c);
    return so_split_ext(ref, i, 0, right);
}

inline So so_rsplit_sub(So ref, So sub, So *right, bool ignorecase) {
    size_t i = so_rfind_sub(ref, sub, ignorecase);
    return so_split_ext(ref, i, sub.len, right);
}


