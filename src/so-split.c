#include "so.h"
#include "so-find.h"
#include "so-split.h"

So _so_split(So *so, size_t i, So *right) {
    if(right) *right = _so_i0(so, i);
    So left = _so_iE(so, i);
    return left;
}

So _so_split_ext(So *so, size_t i, size_t n, So *right) {
    if(right) {
        if(i + n <= _so_len(so)) *right = _so_i0(so, i + n);
        else *right = _so_i0(so, i);
    }
    So left = _so_iE(so, i);
    return left;
}


So _so_split_ch(So *so, char c, So *right) {
    size_t i = so_find_ch(*so, c);
    return _so_split_ext(so, i, 1, right);
}

So _so_split_nch(So *so, char c, So *right) {
    size_t i = so_find_nch(*so, c);
    return _so_split_ext(so, i, 1, right);
}

So _so_split_sub(So *so, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = so_find_sub(*so, sub, attr);
    return _so_split_ext(so, i, so_len(sub), right);
}

So _so_split_nsub(So *so, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = so_find_nsub(*so, sub, attr);
    return _so_split_ext(so, i, so_len(sub), right);
}


So _so_rsplit_ch(So *so, char c, So *right) {
    size_t i = so_rfind_ch(*so, c);
    return _so_split_ext(so, i, 1, right);
}

So _so_rsplit_nch(So *so, char c, So *right) {
    size_t i = so_rfind_nch(*so, c);
    return _so_split_ext(so, i, 1, right);
}

So _so_rsplit_sub(So *so, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = so_rfind_sub(*so, sub, attr);
    return _so_split_ext(so, i, so_len(sub), right);
}

So _so_rsplit_nsub(So *so, So sub, So *right, So_Cmp_Attr attr) {
    size_t i = so_rfind_nsub(*so, sub, attr);
    return _so_split_ext(so, i, so_len(sub), right);
}


